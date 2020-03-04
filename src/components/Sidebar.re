module Styles = {
  open Css;

  let container =
    style([
      media("(min-width: 899px)", [left(`px(8))]),
      position(`absolute),
      top(`px(8)),
      left(`px(-300)),
      width(`px(272)),
      padding(`px(10)),
      borderRadius(`px(5)),
      backgroundColor(`rgba((255, 255, 255, 0.6))),
      transitionProperty("left"),
      transitionDuration(500),
      selector(
        "h3, h4, h5",
        [
          margin2(~v=`px(10), ~h=`zero),
          fontWeight(`num(500)),
          lineHeight(`em(1.2)),
          color(hex("000")),
        ],
      ),
      selector("h3", [fontSize(px(24))]),
      selector("h4", [fontSize(px(18))]),
      selector("h5", [marginBottom(`zero), fontSize(px(14))]),
      selector(
        "hr",
        [
          margin2(~v=`px(20), ~h=`zero),
          borderStyle(`none),
          borderTop(`px(1), `dashed, `hex("c5c5c5")),
          borderBottom(`px(1), `dashed, `hex("f7f7f7")),
        ],
      ),
      selector(
        "a",
        [
          fontWeight(`normal),
          textDecoration(`none),
          color(`hex("b83f45")),
        ],
      ),
      selector(
        "ul",
        [padding(`zero), marginBottom(`px(30)), marginLeft(`px(25))],
      ),
    ]);
};

module SourceLinks = {
  [@react.component]
  let make = () => {
    <span>
      <h5> {React.string("Example")} </h5>
      <a href=Constant.home> {React.string("Source")} </a>
    </span>;
  };
};

module SpeechBubble = {
  open Css;

  [@react.component]
  let make = () => {
    <blockquote
      className={style([
        position(`relative),
        padding(`px(10)),
        backgroundColor(`rgba((0, 0, 0, 0.04))),
        borderRadius(`px(5)),
        borderStyle(`none),
        margin4(~top=`px(20), ~right=`zero, ~bottom=`px(60), ~left=`zero),
        after([
          contentRule(""),
          position(`absolute),
          top(pct(100.0)),
          right(`px(30)),
          border(`px(13), `solid, `transparent),
          borderTopColor(`rgba((0, 0, 0, 0.04))),
        ]),
      ])}>
      <p
        className={style([
          fontSize(`px(15)),
          fontWeight(`num(300)),
          fontStyle(`italic),
          marginTop(`zero),
          marginBottom(`zero),
          before([
            contentRule({js|“|js}),
            position(`absolute),
            top(`px(-20)),
            left(`px(3)),
            fontSize(`px(50)),
            opacity(0.15),
            // Fix manually
            height(`px(65)),
            display(`flex),
            alignItems(`center),
          ]),
          after([
            contentRule({js|”|js}),
            position(`absolute),
            bottom(`px(-42)),
            right(`px(3)),
            fontSize(`px(50)),
            opacity(0.15),
            // Fix manually
            height(`px(65)),
            display(`flex),
            alignItems(`center),
          ]),
        ])}>
        {React.string(
           {|
          ReasonReact is a safer, simpler way to build React components, in Reason.
        |},
         )}
      </p>
      <footer
        className={style([
          position(`absolute),
          bottom(`px(-40)),
          right(`zero),
        ])}>
        <a> {React.string("ReasonReact")} </a>
      </footer>
    </blockquote>;
  };
};

module OfficialResourceLinks = {
  [@react.component]
  let make = () => {
    <ul>
      <li>
        <a href="https://reasonml.github.io/reason-react/docs/en/what-and-why">
          {React.string("What & Why")}
        </a>
      </li>
      <li>
        <a href="https://reasonml.github.io/reason-react/docs/en/simple">
          {React.string("Examples")}
        </a>
      </li>
    </ul>;
  };
};

module CommunityLinks = {
  [@react.component]
  let make = () => {
    <ul>
      <li> <a href="https://reasonml.chat"> {React.string("Forum")} </a> </li>
      <li>
        <a href="https://discord.gg/reasonml"> {React.string("Discord")} </a>
      </li>
      <li>
        <a href="https://twitter.com/reasonml"> {React.string("Twitter")} </a>
      </li>
      <li>
        <a href="https://www.reddit.com/r/reasonml/">
          {React.string("Reddit")}
        </a>
      </li>
      <li>
        <a href="http://stackoverflow.com/questions/tagged/reason-react">
          {React.string("Stack Overflow")}
        </a>
      </li>
    </ul>;
  };
};

[@react.component]
let make =
  React.memo(() => {
    <aside className=Styles.container>
      <header>
        <h3> {React.string("ReasonReact")} </h3>
        <SourceLinks />
      </header>
      <hr />
      <SpeechBubble />
      <hr />
      <h4> {React.string("Official Resources")} </h4>
      <OfficialResourceLinks />
      <h4> {React.string("Community")} </h4>
      <CommunityLinks />
      <footer>
        <hr />
        <em>
          {React.string(
             "If you have other helpful links to share, or find any of the links above no longer work, please ",
           )}
          <a href=Constant.home> {React.string("let us know")} </a>
          {React.string(".")}
        </em>
      </footer>
    </aside>
  });
