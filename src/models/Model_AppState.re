module Todo = Model_Todo;

[@bs.deriving jsConverter]
type t = {todos: list(Todo.t)};

type action =
  | AddTodo(Todo.t)
  | ToggleTodo(string)
  | ToggleAll(bool)
  | DestroyTodo(string)
  | ChangeText(string, string)
  | ClearCompleted;

let reducer = (state, action) => {
  switch (action) {
  | AddTodo(todo) => {todos: state.todos @ [todo]}
  | ToggleTodo(id) => {
      todos:
        state.todos
        ->Belt.List.map(todo => {
            todo.id == id ? {...todo, complete: !todo.complete} : todo
          }),
    }
  | DestroyTodo(id) => {
      todos: state.todos->Belt.List.keep(todo => todo.id != id),
    }
  | ChangeText(id, text) => {
      todos:
        state.todos
        ->Belt.List.map(todo => {todo.id == id ? {...todo, text} : todo}),
    }
  | ToggleAll(complete) => {
      todos: state.todos->Belt.List.map(todo => {...todo, complete}),
    }
  | ClearCompleted => {
      todos: state.todos->Belt.List.keep(todo => !todo.complete),
    }
  };
};

module Dispatch = {
  let todoDispatchContext = React.createContext((_: action) => ());
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
  let make = React.Context.provider(todoDispatchContext);
  let use = () => React.useContext(todoDispatchContext);
};
