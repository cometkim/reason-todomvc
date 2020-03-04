module AppState = Model_AppState;
module Todo = Model_Todo;

module Styles = {
  open Css;

  let container =
    style([
      display(`grid),
      gridTemplateColumns([fr(1.0), fr(2.0), fr(1.0)]),
      height(`px(20)),
      padding2(~v=`px(10), ~h=`px(15)),
      color(`hex("777")),
      before([
        contentRule(""),
        position(`absolute),
        left(`zero),
        right(`zero),
        bottom(`zero),
        height(`px(50)),
        overflow(`hidden),
        unsafe(
          "box-shadow",
          {|
          0 1px 1px rgba(0, 0, 0, 0.2),
          0 8px 0 -3px #f6f6f6,
          0 9px 1px -3px rgba(0, 0, 0, 0.2),
          0 16px 0 -6px #f6f6f6,
          0 17px 2px -6px rgba(0, 0, 0, 0.2)
        |},
        ),
      ]),
      selector("> *", [zIndex(1)]),
      selector("> :nth-child(1)", [textAlign(`left)]),
      selector("> :nth-child(2)", [textAlign(`center)]),
      selector("> :nth-child(3)", [textAlign(`right)]),
    ]);

  let counter = style([]);

  let filters =
    style([
      margin(`zero),
      padding(`zero),
      listStyleType(`none),
      selector(
        "> li",
        [
          display(`inline),
          selector(
            "> a",
            [
              margin2(~v=`px(3), ~h=`px(5)),
              padding2(~v=`px(3), ~h=`px(7)),
              color(`currentColor),
              textDecoration(`none),
              border(`px(1), `solid, `transparent),
              borderRadius(`px(3)),
              hover([borderColor(`rgba((175, 47, 47, 0.1)))]),
              selector(
                "&.selected",
                [borderColor(`rgba((175, 47, 47, 0.2)))],
              ),
            ],
          ),
        ],
      ),
    ]);

  let clearComplete =
    style([
      fontSize(`px(14)),
      color(`currentColor),
      cursor(`pointer),
      lineHeight(`px(20)),
      hover([textDecoration(`underline)]),
    ]);
};

module TodoLeftCounter = {
  [@react.component]
  let make =
    React.memo((~todos: list(Todo.t)) => {
      <div>
        {todos
         ->Belt.List.keep(todo => !todo.complete)
         ->Belt.List.length
         ->string_of_int
         ->(n => n ++ " items left")
         ->React.string}
      </div>
    });
};

module TodoFilters = {
  [@react.component]
  let make =
    React.memo(() => {
      let url = ReasonReactRouter.useUrl();
      let filterClass = id => id === url.hash ? "selected" : "";
      <ul className=Styles.filters>
        <li>
          <a href="#" className={filterClass("")}> {React.string("All")} </a>
        </li>
        <li>
          <a href="#active" className={filterClass("active")}>
            {React.string("Active")}
          </a>
        </li>
        <li>
          <a href="#completed" className={filterClass("completed")}>
            {React.string("Completed")}
          </a>
        </li>
      </ul>;
    });
};

module ClearButton = {
  [@react.component]
  let make =
    React.memo((~hidden) => {
      let dispatch = AppState.Dispatch.use();
      <div hidden>
        <button
          className=Styles.clearComplete
          onClick={_ => dispatch(ClearCompleted)}>
          {React.string("Clear completed")}
        </button>
      </div>;
    });
};

[@react.component]
let make =
  React.memo((~todos: list(Todo.t)) => {
    let hasCompleted =
      todos->Belt.List.keep(todo => todo.complete)->Belt.List.length > 0;

    <div className=Styles.container>
      <TodoLeftCounter todos />
      <TodoFilters />
      <ClearButton hidden={!hasCompleted} />
    </div>;
  });
