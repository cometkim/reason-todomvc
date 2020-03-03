module Styles = {
  open Css;

  let container = style([width(pct(100.0))]);

  let input =
    style([
      position(`relative),
      margin(`zero),
      padding(`px(16)),
      paddingLeft(`px(60)),
      borderStyle(`none),
      width(pct(100.0)),
      fontSize(`px(24)),
      lineHeight(`em(1.4)),
      boxSizing(`borderBox),
      height(rem(3.0)),
      background(`rgba((0, 0, 0, 0.003))),
      boxShadow(
        Shadow.box(
          ~y=`px(-2),
          ~blur=`px(1),
          ~inset=true,
          `rgba((0, 0, 0, 0.03)),
        ),
      ),
      placeholder([color(hex("#bcbcbc")), fontStyle(italic)]),
    ]);
};

type submit = string => unit;

[@react.component]
let make =
  React.memo((~onSubmit: submit) => {
    let inputRef = React.useRef(Js.Nullable.null);

    let handleSubmit =
      React.useCallback1(
        event => {
          event->ReactEvent.Form.preventDefault;
          inputRef
          ->React.Ref.current
          ->Js.Nullable.toOption
          ->Belt.Option.map(inputRef => {
              inputRef->ReactDOMRe.domElementToObj##value->onSubmit;
              %raw
              "inputRef.value = ''";
            })
          ->ignore;
        },
        [|onSubmit|],
      );

    <form onSubmit=handleSubmit>
      <input
        ref={ReactDOMRe.Ref.domRef(inputRef)}
        id="todo-input"
        name="todo-input"
        placeholder="What needs to be done?"
        className=Styles.input
        autoComplete="off"
      />
    </form>;
  });
