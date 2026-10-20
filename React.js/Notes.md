1. what are import and export in react js?

2. Real DOM vs Virtual DOM

3. What is JSX?
- JSX stands for JavaScript XML. It is a syntax extension for JavaScript that allows you to write HTML-like code within your JavaScript code. 

4. Now Let's create React Folder Using Vite

npm create vite
- Then select react and then select JavaScript
- Now we will work in the src folder > App.jsx 

5. To run our react app we will use the command
- npm run dev

6. App.jsx
- rafce
- It will create a functional component for us.

## Hooks

image of hooks.jpg

1. useState - to state management
2. useEffect - to handle side effects in functional components (A side effect is anything that affects something outside the scope of the function being executed. For example, fetching data from an API, updating the DOM, or setting up a subscription are all side effects.)
3. useContext - to manage state globally (Context provides a way to pass data through the component tree without having to pass props down manually at every level.)
4. useReducer - To manage state in a more complex way (useReducer is a hook that is used for managing state in a more complex way than useState. It is similar to Redux, but it is built into React and does not require any additional libraries.)
5. useCallback - to memoize a function (useCallback is a hook that is used to memoize a function. It is useful when you have a function that is passed as a prop to a child component and you want to prevent the child component from re-rendering unnecessarily.)
6. useMemo - to memoize a value (useMemo is a hook that is used to memoize a value. It is useful when you have a value that is expensive to compute and you want to prevent it from being re-computed unnecessarily.)
7. useRef - to access a DOM element (useRef is a hook that is used to access a DOM element. It is useful when you want to focus an input field, scroll to a specific element, or measure the size of an element.)

### useState
it will create a state for us.

```js
import React, { useState } from 'react'

const App = () => {
  const [count, setCount] = useState(0);

  return (
    <div>
      <h1>Count is {count}</h1>
      <button onClick={() => setCount(count + 1)}>Increment</button>
    </div>
  )
}

export default App
```

### useEffect
it will run a function when the component is mounted.

```js
import React, { useState, useEffect } from 'react'

const App = () => {
  const [count, setCount] = useState(0);

  useEffect(() => {
    console.log('Component mounted');
  }, []);
  
  return (
    <div>
      <h1>Count is {count}</h1>
      <button onClick={() => setCount(count + 1)}>Increment</button>
    </div>
  )
}

export default App
```

### useContext
it will create a context for us.


## State
image of state

## Props