module.exports = {
  verbose: true,
  "roots": [
    "<rootDir>/tests"
  ],
  "testMatch": [
    "<rootDir>/tests/**/*_test.{js,bs.js}"
  ],
  "transform": {
    "\\.(png|jpg|gif|svg)$": "<rootDir>/tests/fileTransformer.js",
  },
  snapshotSerializers: [
    'jest-emotion',
  ],
};
