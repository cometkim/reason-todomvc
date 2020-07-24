module Container = [%styled.footer {|
  margin: 65px auto 0 auto;
  font-size: 10px;
  color: #bfbfbf;
  text-align: center;
  text-shadow: 0 1px 0 rgba(255,255,255,.5);
  & > p {
    line-height: 1em;
    a {
      color: currentColor;
      font-weight: 400;
      text-decoration: none;
      :hover {
        text-decoration: underline;
      }
    }
  }
|}];

[@react.component]
let make =
  React.memo(() => {
    <Container>
      <p> {React.string("Double-click to edit a todo")} </p>
      <p>
        {React.string("Created by ")}
        <a href="https://github.com/cometkim"> {React.string("cometkim")} </a>
      </p>
      <p>
        {React.string("Part of ")}
        <a href="http://todomvc.com"> {React.string("TodoMVC")} </a>
      </p>
    </Container>
  });
