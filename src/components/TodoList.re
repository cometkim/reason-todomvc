module AppState = Model_AppState;

module Styles = {
  open Css;

  let container =
    style([listStyleType(none), margin(zero), paddingLeft(zero)]);

  let itemWrapper =
    style([
      display(`flex),
      alignItems(center),
      border(px(1), `solid, hex("dddddd")),
      borderTopStyle(none),
    ]);

  let toolsWrapper =
    style([
      display(`grid),
      gridTemplateColumns([fr(1.0), fr(1.0), fr(1.0)]),
    ]);

  let textRight = style([textAlign(`right)]);
};

[@react.component]
let make = (~todos: array(Model_Todo.t)) => {
  let dispatch = AppState.Dispatch.use();

  let leftItemCount =
    todos->Belt.Array.keep(todo => !todo.complete)->Belt.Array.length;

  let completedItemCount =
    todos->Belt.Array.keep(todo => todo.complete)->Belt.Array.length;

  <>
    <ul className=Styles.container>
      {todos
       ->Belt.Array.map(todo => {
           <li className=Styles.itemWrapper> <TodoItem todo /> </li>
         })
       ->React.array}
    </ul>
    <div className=Styles.toolsWrapper>
      <div>
        {React.string(leftItemCount->string_of_int ++ " items left")}
      </div>
      <div>
        <a href="#"> {React.string("All")} </a>
        <a href="#active"> {React.string("Active")} </a>
        <a href="#completed"> {React.string("Completed")} </a>
      </div>
      <div>
        {completedItemCount > 0
           ? <button
               className=Styles.textRight
               onClick={_ => dispatch(ClearCompleted)}>
               {React.string("Clear complated")}
             </button>
           : React.null}
      </div>
    </div>
  </>;
};
