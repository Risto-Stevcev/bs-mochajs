type mocha;
type done_callback = unit => unit;

[@bs.send] external timeout : (mocha, int) => unit = "timeout";
[@bs.val] external _describe_this : (string, [@bs.this] ((mocha, unit) => unit)) => unit = "describe";
[@bs.val] external _describe : (string, unit => unit) => unit = "describe";
[@bs.val] external _it_this : (string, [@bs.this] ((mocha, unit) => unit)) => unit = "it";
[@bs.val] external _it : (string, unit => unit) => unit = "it";
[@bs.val] external _it_this' : (string, [@bs.this] ((mocha, done_callback) => unit)) => unit = "it";
[@bs.val] external _it' : (string, done_callback => unit) => unit = "it";

let describe: (string, ~ms: int=?, unit => unit) => unit =
  (description, ~ms: option(int)=?, callback) =>
    switch ms {
    | Some(ms') => _describe_this(description, [@bs.this] (mocha, _) => {
        timeout(mocha, ms');
        callback()
      })
    | None => _describe(description, callback)
    };

let it: (string, ~ms: int=?, unit => unit) => unit =
  (description, ~ms: option(int)=?, callback) =>
    switch ms {
    | Some(ms') => _it_this(description, [@bs.this] (mocha, _) => {
        timeout(mocha, ms');
        callback()
      })
    | None => _it(description, callback)
    };

/* Version of `it` that provides `done` in the callback for async tests */
let it': (string, ~ms: int=?, done_callback => unit) => unit =
  (description, ~ms: option(int)=?, callback) =>
    switch ms {
    | Some(ms') => _it_this'(description, [@bs.this] (mocha, done_) => {
        timeout(mocha, ms');
        callback(done_)
      })
    | None => _it'(description, callback)
    };

[@bs.module "assert"] external eq : ('a, 'a) => unit = "deepEqual";

[@bs.module "assert"] external neq : ('a, 'a) => unit = "notDeepEqual";

[@bs.module "assert"] external should_be_ok : Js.boolean => unit = "ok";

[@bs.module "assert"]
external fail :
  (~actual: 'a, ~expected: 'a, ~message: string=?, ~operator: string=?, unit) => unit =
  "fail";


[@bs.val] external before : (unit => unit) => unit = "before";
[@bs.val] external before' : (done_callback => unit) => unit = "before";
[@bs.val] external before_each : (unit => unit) => unit = "beforeEach";
[@bs.val] external before_each' : (done_callback => unit) => unit = "beforeEach";
[@bs.val] external after : (unit => unit) => unit = "after";
[@bs.val] external after' : (done_callback => unit) => unit = "after";
[@bs.val] external after_each : (unit => unit) => unit = "afterEach";
[@bs.val] external after_each' : (done_callback => unit) => unit = "afterEach";


type expect('a) = {
  to_be: 'a => unit,
  to_not_be: 'a => unit,
  to_fail: 'a => unit
};

let expect = (actual) => {
  to_be: (expected) => eq(actual, expected),
  to_not_be: (expected) => neq(actual, expected),
  to_fail: (expected) => fail(~actual, ~expected, ())
};
