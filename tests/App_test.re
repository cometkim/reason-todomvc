open Jest;
open Expect;
open ReactTestingLibrary;

describe("Home component", () => {
  test("renders without crashing", () => {
    render(<App />)->container->expect->toMatchSnapshot
  })
});
