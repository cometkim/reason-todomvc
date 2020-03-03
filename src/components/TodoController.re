module AppState = Model_AppState;

module Styles = {
  open Css;

  let container =
    style([
      display(`grid),
      gridTemplateColumns([fr(1.0), fr(1.0), fr(1.0)]),
    ]);
};

[@react.component]
let make = (~todos: array(Model_Todo.t)) => {
  let dispatch = AppState.Dispatch.use();

  let count = todos->Belt.Array.length;
  let itemsLeft =
    todos->Belt.Array.keep(todo => !todo.complete)->Belt.Array.length;
  let hasComplete = count - itemsLeft > 0;

  <div className=Styles.container>
    <div> {React.string(itemsLeft->string_of_int ++ " items left")} </div>
    <div>
      <a href="#"> {React.string("All")} </a>
      <a href="#active"> {React.string("Active")} </a>
      <a href="#completed"> {React.string("Completed")} </a>
    </div>
    <div>
      {hasComplete
         ? <button onClick={_ => dispatch(ClearCompleted)}>
             {React.string("Clear complated")}
           </button>
         : React.null}
    </div>
  </div>;
};
