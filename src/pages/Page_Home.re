module AppState = Model_AppState;

module Styles = {
  open Css;

  let container =
    style([
      display(flexBox),
      flexDirection(column),
      width(pct(100.0)),
      alignItems(center),
    ]);
};

let id_gen = ref(0);

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(AppState.reducer, {todos: [||]});

  let onSubmit =
    React.useCallback1(
      v =>
        if (v != "") {
          dispatch(AddTodo({id: id_gen^, text: v, complete: false}));
          id_gen := id_gen^ + 1;
        },
      [|dispatch|],
    );

  <div className=Styles.container>
    <Header />
    <main>
      <Form onSubmit />
      <AppState.Dispatch value=dispatch>
        <TodoList todos={state.todos} />
      </AppState.Dispatch>
    </main>
    <Footer />
  </div>;
};
