import json
import os
import subprocess
from types import SimpleNamespace

import pytest

from test_check_duplicate_markers import (
    TOOLS,
    annotation,
    checker,
    comparison,
    contract,
)


@pytest.fixture
def command(tmp_path, monkeypatch):
    source = tmp_path / "src/example.cpp"
    source.parent.mkdir()
    source.write_text(annotation("?Alias") + annotation("?Canonical"))
    membership = tmp_path / "membership.json"
    membership.write_text(json.dumps(contract()))
    target = SimpleNamespace(
        source_paths=[source.parent],
        encoding="utf-8",
        data_sources=[],
        marker_aliases={},
    )
    monkeypatch.setattr(checker, "ROOT", tmp_path)
    monkeypatch.setattr(checker, "MEMBERSHIP", membership)
    monkeypatch.setattr(checker, "load_target", lambda: target)
    monkeypatch.setattr(checker, "provenance", lambda _: {})
    monkeypatch.setattr(checker, "verify_inputs", lambda *_: None)
    monkeypatch.setattr(checker.sys, "argv", ["check_duplicate_markers.py"])
    calls = []

    def from_target(_):
        calls.append(True)
        return comparison([checker.TextFile.from_file(source)])

    monkeypatch.setattr(checker.DiagnosticCompare, "from_target", from_target)
    return SimpleNamespace(
        source=source, membership=membership, target=target, calls=calls
    )


@pytest.mark.parametrize("quiet", [False, True])
def test_command_accepts_only_after_live_proof(command, monkeypatch, capsys, quiet):
    if quiet:
        monkeypatch.setattr(
            checker.sys, "argv", ["check_duplicate_markers.py", "--quiet"]
        )
    assert checker.main() == 0
    assert command.calls == [True]
    output = capsys.readouterr()
    assert output.err == ""
    assert ("1 proven folded TEMPLATE groups" in output.out) != quiet


@pytest.mark.parametrize(
    "text",
    [
        annotation("?Wrong") + annotation("?Canonical"),
        annotation("?Canonical"),
        annotation("?Alias", "FUNCTION") + annotation("?Canonical"),
        annotation("?Alias") + annotation("?Canonical") + annotation("?Extra"),
        annotation("?Alias")
        + annotation("?Canonical")
        + annotation("?X", "FUNCTION", "", "0x00600000") * 2,
    ],
)
def test_command_negative_source_fixtures_fail_before_proof(command, text, capsys):
    command.source.write_text(text)
    assert checker.main() == 1
    assert not command.calls
    assert "failed" in capsys.readouterr().err


def test_command_malformed_metadata_does_not_fall_back_to_acceptance(command):
    command.membership.write_text("{malformed")
    with pytest.raises(ValueError):
        checker.main()
    assert not command.calls


def test_command_missing_artifacts_do_not_fall_back_to_acceptance(command, monkeypatch):
    def unavailable(_):
        raise FileNotFoundError("Game.pdb")

    monkeypatch.setattr(checker.DiagnosticCompare, "from_target", unavailable)
    with pytest.raises(FileNotFoundError, match="Game.pdb"):
        checker.main()


def test_command_no_success_metadata_fails(command, monkeypatch):
    monkeypatch.setattr(
        checker.DiagnosticCompare,
        "from_target",
        lambda _: comparison([checker.TextFile.from_file(command.source)], prove=False),
    )
    with pytest.raises(ValueError, match="successful folded proof"):
        checker.main()


def test_command_source_changes_during_proof_fail(command, monkeypatch):
    def mutate(_):
        result = comparison([checker.TextFile.from_file(command.source)])
        command.source.write_text(annotation("?Canonical"))
        return result

    monkeypatch.setattr(checker.DiagnosticCompare, "from_target", mutate)
    with pytest.raises(ValueError, match="source files changed"):
        checker.main()


def test_command_membership_changes_during_proof_fail(command, monkeypatch):
    def mutate(_):
        result = comparison([checker.TextFile.from_file(command.source)])
        command.membership.write_text("{}")
        return result

    monkeypatch.setattr(checker.DiagnosticCompare, "from_target", mutate)
    with pytest.raises(ValueError, match="membership changed"):
        checker.main()


@pytest.mark.parametrize(
    "field,value",
    [("data_sources", ["untrusted.json"]), ("marker_aliases", {"NEW": "TEMPLATE"})],
)
def test_command_rejects_metadata_injection_configuration(command, field, value):
    setattr(command.target, field, value)
    with pytest.raises(ValueError, match="direct-marker/no-data-source"):
        checker.main()
    assert not command.calls


@pytest.mark.parametrize("invocation", ["executable", "venv", "dispatcher"])
def test_canonical_entrypoint_from_another_directory(tmp_path, invocation):
    environment = dict(os.environ, PATH=os.defpath)
    executable = TOOLS / "check_duplicate_markers.py"
    if invocation == "executable":
        environment["PATH"] = f"{TOOLS.parent / '.venv/bin'}{os.pathsep}{os.defpath}"
        command = [str(executable)]
    elif invocation == "venv":
        command = [str(TOOLS.parent / ".venv/bin/python"), str(executable)]
    else:
        command = [str(TOOLS / "check.sh"), "duplicates"]
    result = subprocess.run(
        command + ["--help"],
        cwd=tmp_path,
        env=environment,
        capture_output=True,
        text=True,
        timeout=30,
    )
    assert result.returncode == 0, result.stderr
    assert "usage: check_duplicate_markers.py" in result.stdout
    assert "live comparator proof" in " ".join(result.stdout.split())
    assert not executable.with_suffix(".sh").exists()
