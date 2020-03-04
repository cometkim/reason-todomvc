module AppState = Model_AppState;
module Todo = Model_Todo;

module Styles = {
  open Css;

  let container =
    style([listStyleType(none), margin(zero), paddingLeft(zero)]);

  let itemWrapper =
    style([
      position(`relative),
      fontSize(`px(24)),
      display(`flex),
      alignItems(center),
    ]);

  let toggleAll =
    style([
      position(`absolute),
      textAlign(`center),
      borderStyle(`none),
      opacity(0.0),
      selector(
        "& + label",
        [
          position(`absolute),
          top(`px(-52)),
          left(`px(-13)),
          width(`px(60)),
          height(`px(34)),
          fontSize(`zero),
          transform(`rotate(`deg(90.0))),
          before([
            contentRule({js|❯|js}),
            fontSize(`px(22)),
            color(`hex("e6e6e6")),
            padding2(~v=`px(10), ~h=`px(27)),
          ]),
        ],
      ),
    ]);
};

[@react.component]
let make = (~todos: array(Todo.t)) => {
  <>
    <input id="toggle-all" className=Styles.toggleAll type_="checkbox" />
    <label htmlFor="toggle-all" />
    <ul className=Styles.container>
      {todos
       ->Belt.Array.map(todo => {
           <li key={todo.id->string_of_int} className=Styles.itemWrapper>
             <TodoItem todo />
           </li>
         })
       ->React.array}
    </ul>
  </>;
};
