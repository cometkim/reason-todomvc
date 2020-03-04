Css.(
  global("html, body", [margin(`zero), padding(`zero)]),
  global(
    "body",
    [
      fontFamily("'Helvetica Neue', Helvetica, Arial, sans-serif"),
      fontSize(`px(14)),
      lineHeight(`em(1.4)),
      color(`hex("4d4d4d")),
      background(`hex("f5f5f5")),
      minWidth(px(230)),
      maxWidth(px(550)),
      margin2(~v=`zero, ~h=`auto),
      fontWeight(`num(300)),
      unsafe("-webkit-font-smoothing", "antialiased"),
      media("(min-width: 899px)", [width(`auto), paddingLeft(`px(300))]),
    ],
  ),
  global(
    "button",
    [
      margin(`zero),
      padding(`zero),
      borderStyle(`none),
      background(`none),
      verticalAlign(`baseline),
      fontFamily("inherit"),
      fontWeight(`inherit_),
      unsafe("appearance", "none"),
      unsafe("font-smoothing", "antialiased"),
    ],
  ),
);

ReactDOMRe.renderToElementWithId(<App />, "root");
