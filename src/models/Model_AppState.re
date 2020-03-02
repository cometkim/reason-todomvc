type t = {todos: array(Model_Todo.t)};

type action =
  | AddTodo(Model_Todo.t)
  | ToggleTodo(int)
  | DestroyTodo(int)
  | ChangeText(int, string)
  | ClearCompleted;

let reducer = (state, action) => {
  switch (action) {
  | AddTodo(todo) => {todos: state.todos->Belt.Array.concat([|todo|])}
  | ToggleTodo(id) => {
      todos:
        state.todos
        ->Belt.Array.map(todo => {
            todo.id == id ? {...todo, complete: !todo.complete} : todo
          }),
    }
  | DestroyTodo(id) => {
      todos: state.todos->Belt.Array.keep(todo => todo.id != id),
    }
  | ChangeText(id, text) => {
      todos:
        state.todos
        ->Belt.Array.map(todo => {todo.id == id ? {...todo, text} : todo}),
    }
  | ClearCompleted => {
      todos: state.todos->Belt.Array.keep(todo => !todo.complete),
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
