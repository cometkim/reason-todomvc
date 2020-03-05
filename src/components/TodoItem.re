[@bs.module "../assets/checked.svg"] external checkedSrc: string = "default";
[@bs.module "../assets/unchecked.svg"]
external uncheckedSrc: string = "default";

module AppState = Model_AppState;
module Todo = Model_Todo;

module Styles = {
  open Css;

  let view =
    style([
      display(`block),
      width(pct(100.0)),
      hover([selector("> button", [display(block)])]),
      borderBottom(`px(1), `solid, `hex("ededed")),
    ]);

  let edit =
    style([
      position(`relative),
      margin(`zero),
      marginLeft(`px(43)),
      width(pct(100.0)),
      fontSize(`px(24)),
      fontFamily("inherit"),
      fontWeight(`inherit_),
      lineHeight(`em(1.4)),
      color(`currentColor),
      padding2(~v=`px(12), ~h=`px(16)),
      border(`px(1), `solid, `hex("999")),
      borderBottomStyle(`none),
      boxShadow(
        Shadow.box(
          ~inset=true,
          ~y=`px(-1),
          ~blur=`px(5),
          `rgba((0, 0, 0, 0.2)),
        ),
      ),
      boxSizing(`borderBox),
      unsafe("fontSmoothing", "antialiased"),
    ]);

  let toggle =
    style([
      opacity(0.0),
      textAlign(`center),
      width(`px(40)),
      height(`px(40)),
      position(`absolute),
      top(`zero),
      bottom(`zero),
      margin2(~v=`auto, ~h=`zero),
      borderStyle(`none),
      background(`none),
      selector(
        "& + label",
        [
          backgroundImage(`url(uncheckedSrc)),
          backgroundRepeat(`noRepeat),
          unsafe("backgroundPosition", "center left"),
        ],
      ),
      selector(
        "&:checked + label",
        [
          backgroundImage(`url(checkedSrc)),
          color(`hex("d9d9d9")),
          textDecoration(`lineThrough),
        ],
      ),
    ]);

  let text =
    style([
      display(`block),
      wordBreak(`breakAll),
      lineHeight(`em(1.2)),
      padding4(
        ~top=`px(15),
        ~right=`px(15),
        ~bottom=`px(15),
        ~left=`px(60),
      ),
      transition(~duration=400, "color"),
    ]);

  let destroy =
    style([
      display(`none),
      position(`absolute),
      top(`zero),
      right(`px(10)),
      bottom(`zero),
      width(`px(40)),
      height(`px(40)),
      margin2(~v=`auto, ~h=`zero),
      marginBottom(`px(11)),
      fontSize(`px(30)),
      color(`hex("cc9a9a")),
      transition(~duration=200, ~timingFunction=`easeOut, "color"),
      hover([color(`hex("af5b5e"))]),
      after([contentRule({js|×|js})]),
    ]);

  let completed = style([textDecoration(lineThrough)]);

  let hidden = style([display(none)]);
};

[@react.component]
let make =
  React.memo((~todo: Todo.t) => {
    let dispatch = AppState.Dispatch.use();

    let url = ReasonReactRouter.useUrl();
    let hidden =
      switch (todo.complete, url.hash) {
      | (true, "active") => true
      | (false, "completed") => true
      | _ => false
      };

    let handleToggle = _ => {
      dispatch(ToggleTodo(todo.id));
    };

    let handleDestroy = _ => {
      dispatch(DestroyTodo(todo.id));
    };

    let inputRef = React.useRef(Js.Nullable.null);
    let getEl = inputRef => inputRef->React.Ref.current->Js.Nullable.toOption;

    let (editing, setEditing) = React.useState(_ => false);

    let editStart = _ => setEditing(_ => true);
    let editEnd = _ => setEditing(_ => false);
    let onKeyDown = event =>
      if (event->ReactEvent.Keyboard.key === "Enter") {
        setEditing(_ => false);
      };

    React.useEffect1(
      () => {
        if (editing) {
          inputRef
          ->getEl
          ->Belt.Option.map(el => {el->ReactDOMRe.domElementToObj##focus()})
          ->ignore;
        };
        None;
      },
      [|editing|],
    );

    React.useEffect2(
      () => {
        let text =
          switch (editing, inputRef->getEl) {
          | (false, Some(inputEl)) =>
            inputEl->ReactDOMRe.domElementToObj##value
          | _ => todo.text
          };
        if (text !== "" && text !== todo.text) {
          dispatch(ChangeText(todo.id, text));
        };
        None;
      },
      (todo, editing),
    );

    <>
      <div
        className={Css.merge([
          Styles.view,
          hidden ? Styles.hidden : "",
          editing ? Styles.hidden : "",
        ])}>
        <input
          className=Styles.toggle
          type_="checkbox"
          checked={todo.complete}
          onChange=handleToggle
        />
        <label className=Styles.text onDoubleClick=editStart>
          todo.text->React.string
        </label>
        <button className=Styles.destroy onClick=handleDestroy />
      </div>
      <input
        ref={ReactDOMRe.Ref.domRef(inputRef)}
        className={Css.merge([
          Styles.edit,
          hidden ? Styles.hidden : "",
          !editing ? Styles.hidden : "",
        ])}
        defaultValue={todo.text}
        autoFocus=true
        onKeyDown
        onBlur=editEnd
      />
    </>;
  });
