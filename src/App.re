module AppState = Model_AppState;

let id = HexoId.create(8);

module Styles = {
  open Css;

  let container =
    style([
      position(`relative),
      background(`hex("fff")),
      marginTop(`px(130)),
      marginBottom(`px(40)),
      // boxShadow(
      //   Shadow.box(~y=`px(2), ~blur=`px(4), `rgba(0, 0, 0, 0.2))
      // ),
      unsafe(
        "boxShadow",
        "0 2px 4px 0 rgba(0, 0, 0, 0.2), 0 25px 50px 0 rgba(0, 0, 0, 0.1)",
      ),
    ]);

  let main =
    style([
      position(`relative),
      borderTop(`px(1), `solid, `hex("e6e6e6")),
      zIndex(2),
    ]);
};

let defaultState: AppState.t = {init: false, todos: []};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(AppState.reducer, defaultState);
  React.useEffect1(
    _ => {
      state.init
        ? state
          ->Js.Json.stringifyAny
          ->Belt.Option.map(json => {
              Dom.Storage2.localStorage->Dom.Storage2.setItem(
                "todo-state",
                json,
              )
            })
          ->ignore
        : dispatch(
            INIT(
              [%raw "JSON.parse(localStorage.getItem('todo-state'))"]
              ->Js.Nullable.toOption
              ->Belt.Option.getWithDefault(defaultState),
            ),
          );
      None;
    },
    [|state|],
  );

  let todos = state.todos;
  let hasTodos = todos->Belt.List.length > 0;
  let onSubmit =
    React.useCallback1(
      v =>
        if (v != "") {
          dispatch(AddTodo({id: id->HexoId.make, text: v, complete: false}));
        },
      [|dispatch|],
    );

  <>
    <Sidebar />
    <section className=Styles.container>
      <header> <Title /> <Form onSubmit /> </header>
      <AppState.Dispatch value=dispatch>
        <main className=Styles.main hidden={!hasTodos}>
          <TodoList todos />
        </main>
        <footer hidden={!hasTodos}> <TodoController todos /> </footer>
      </AppState.Dispatch>
    </section>
    <Footer />
  </>;
};
