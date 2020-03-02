module AppState = Model_AppState;

module Styles = {
  open Css;

  let container =
    style([
      position(relative),
      display(`flex),
      justifyContent(spaceBetween),
      alignItems(center),
      width(pct(100.0)),
      fontSize(rem(1.5)),
      height(rem(3.0)),
      padding2(~h=rem(1.0), ~v=rem(0.0)),
      borderStyle(none),
      hover([selector("> button", [after([display(block)])])]),
    ]);

  let destroy =
    style([
      width(rem(2.0)),
      height(rem(2.0)),
      background(none),
      borderStyle(none),
      after([display(none), contentRule({js|×|js}), fontSize(rem(1.5))]),
    ]);

  let completed = style([textDecoration(lineThrough)]);

  let disable = style([display(none)]);
};

[@react.component]
let make =
  React.memo((~todo: Model_Todo.t) => {
    let dispatch = AppState.Dispatch.use();

    let url = ReasonReactRouter.useUrl();
    let filterStyle =
      switch (todo.complete, url.hash) {
      | (true, "active") => Styles.disable
      | (false, "completed") => Styles.disable
      | _ => ""
      };

    let handleToggle = _ => {
      dispatch(ToggleTodo(todo.id));
    };

    let handleDestroy = _ => {
      dispatch(DestroyTodo(todo.id));
    };

    let (editing, setEditing) = React.useState(_ => false);
    let handleDbClick = _ => {
      setEditing(_ => true);
    };
    let handleKeydown = e =>
      if (ReactEvent.Keyboard.key(e) == "Enter") {
        dispatch(ChangeText(todo.id, ReactEvent.Keyboard.target(e)##value));
        setEditing(_ => false);
      };
    let handleBlur = _ => {
      setEditing(_ => false);
    };

    editing
      ? <input
          className=Styles.container
          id={"edit-todo-" ++ todo.id->string_of_int}
          onKeyDown=handleKeydown
          onBlur=handleBlur
          autoFocus=true
        />
      : <div
          className={Css.merge([Styles.container, filterStyle])}
          onDoubleClick=handleDbClick>
          <div>
            <input
              type_="checkbox"
              checked={todo.complete}
              onChange=handleToggle
            />
            <span className={todo.complete ? Styles.completed : ""}>
              todo.text->React.string
            </span>
          </div>
          <button className=Styles.destroy onClick=handleDestroy />
        </div>;
  });
