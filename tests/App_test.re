open Jest;
open Expect;
open ReactTestingLibrary;

describe("Home component", () => {
  test("renders without crashing", () => {
    <App />
    ->render
    ->container
    ->expect
    ->toMatchSnapshot
  });
});
