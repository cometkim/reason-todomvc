module Form = [%styled.form {|
  width: 100%;
|}];

module Input = [%styled.input {|
  position: relative;
  margin: 0;
  padding: 16px 16px 16px 60px;
  border-style: none;
  width: 100%;
  font-size: 24px;
  line-height: 1.4em;
  font-family: inherit;
  font-weight: inherit;
  box-sizing: border-box;
  box-shadow: inset 0px -2px 1px 0px rgba(0, 0, 0, 0.03);
  background: rgba(0, 0, 0, 0.003);

  ::placeholder {
    color: #e6e6e6;
    font-style: italic;
    font-weight: 300;
  }
|}];

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

    <Form onSubmit=handleSubmit>
      <Input
        ref={ReactDOMRe.Ref.domRef(inputRef)}
        id="todo-input"
        name="todo-input"
        placeholder="What needs to be done?"
        autoComplete="off"
      />
    </Form>;
  });
