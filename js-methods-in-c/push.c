// Do this as the first thing so that any code reading it knows the right env.
process.env.BABEL_ENV = 'test';
process.env.NODE_ENV = 'test';
process.env.PUBLIC_URL = '';

const readline = require('readline');
const { exec, execSync } = require('child_process');
const handleError = (error, stdout, stderr) => {
  if (error) {
    console.log('ERR: Exiting with code', error.code);
    console.log(stderr.toString());
    process.exit(1);
  }
};

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const runScript = function(prompt, script) {
  return new Promise((res, rej) => {
    rl.question(prompt, function(answer) {
      if (answer.toLowerCase() === 'y') {
        execSync(script, { stdio: 'inherit' }, handleError);
      }
      res(0);
    });
  });
};

runScript(
  '[PRECOMMIT] Run all test suites? (Y/n) ',
  'npm test -- precommit'
).then(() => {
  runScript(
    '[PRECOMMIT] Test optimized production build? (Y/n) ',
    'npm run build'
  ).then(() => {
    rl.close();
  });
});


"precommit": "node scripts/precommit.js < /dev/tty && pretty-quick --staged"