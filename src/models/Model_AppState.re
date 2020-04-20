module Todo = Model_Todo;

[@bs.deriving jsConverter]
type t = {
  init: bool,
  todos: list(Todo.t),
};

type action =
  | INIT(t)
  | AddTodo(Todo.t)
  | ToggleTodo(string)
  | ToggleAll(bool)
  | DestroyTodo(string)
  | ChangeText(string, string)
  | ClearCompleted;

let reducer = (state, action) =>
  state.init
    ? switch (action) {
      | AddTodo(todo) => {...state, todos: state.todos @ [todo]}
      | ToggleTodo(id) => {
          ...state,
          todos:
            state.todos
            ->Belt.List.map(todo => {
                todo.id == id ? {...todo, complete: !todo.complete} : todo
              }),
        }
      | DestroyTodo(id) => {
          ...state,
          todos: state.todos->Belt.List.keep(todo => todo.id != id),
        }
      | ChangeText(id, text) => {
          ...state,
          todos:
            state.todos
            ->Belt.List.map(todo => {todo.id == id ? {...todo, text} : todo}),
        }
      | ToggleAll(complete) => {
          ...state,
          todos: state.todos->Belt.List.map(todo => {...todo, complete}),
        }
      | ClearCompleted => {
          ...state,
          todos: state.todos->Belt.List.keep(todo => !todo.complete),
        }
      | _ => state
      }
    : (
      switch (action) {
      | INIT(initialState) => {...initialState, init: true}
      | _ => state
      }
    );

module Dispatch = {
  let todoDispatchContext = React.createContext((_: action) => ());
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(todoDispatchContext);
  let use = () => React.useContext(todoDispatchContext);
};
