[@react.component]
let make = (~label, ~onSubmit) => {
  let (editing, setEditing) = React.useState(() => false);
  let (value, onChange) = React.useState(() => label);
  let onCancel = _evt => setEditing(_ => false);
  let onFocus = event => event->ReactEvent.Focus.target##select();

  React.useEffect1(
    () => {
      onChange(_ => label);
      None;
    },
    [|label|],
  );

  if (editing) {
    <form
      onSubmit={_ => {
        setEditing(_ => false);
        onSubmit(value);
      }}
      onBlur=onCancel>
      <input
        onBlur=onCancel
        onFocus
        onChange={event => onChange(event->ReactEvent.Form.target##value)}
        value
      />
    </form>;
  } else {
    <span onDoubleClick={_evt => setEditing(_ => true)}>
      value->React.string
    </span>;
  };
};
