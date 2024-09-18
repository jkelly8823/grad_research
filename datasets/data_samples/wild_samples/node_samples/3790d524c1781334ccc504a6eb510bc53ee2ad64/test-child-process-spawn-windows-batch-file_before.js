'use strict';

// Node.js on Windows should not be able to spawn batch files directly,
// only when the 'shell' option is set. An undocumented feature of the
// Win32 CreateProcess API allows spawning .bat and .cmd files directly
// but it does not sanitize arguments. We cannot do that automatically
// because it's sometimes impossible to escape arguments unambiguously.
//
// Expectation: spawn() and spawnSync() raise EINVAL if and only if:
//
// 1. 'shell' option is unset
// 2. Platform is Windows
// 3. Filename ends in .bat or .cmd, case-insensitive
//
// exec() and execSync() are unchanged.

const common = require('../common');
const cp = require('child_process');
const assert = require('assert');
const { isWindows } = common;

const arg = '--security-revert=CVE-2024-27980';
const isRevert = process.execArgv.includes(arg);

const expectedCode = isWindows && !isRevert ? 'EINVAL' : 'ENOENT';
const expectedStatus = isWindows ? 1 : 127;

const suffixes =
    'BAT bAT BaT baT BAt bAt Bat bat CMD cMD CmD cmD CMd cMd Cmd cmd'
    .split(' ');

if (process.argv[2] === undefined) {
  const a = cp.spawnSync(process.execPath, [__filename, 'child']);
  const b = cp.spawnSync(process.execPath, [arg, __filename, 'child']);
  assert.strictEqual(a.status, 0);
  assert.strictEqual(b.status, 0);
  return;
}