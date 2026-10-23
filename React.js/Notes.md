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

### Form Handling & Preventing Page Refresh

```js
import React from 'react'

const Form_Handling = () => {

  // This function Prevents the form to refresh the page when the submit button is clicked
  const submitHandler = (event) => {
    event.preventDefault()
    console.log('Form submitted');
  }

  return (
    <div>
      <form onSubmit={submitHandler}>
        <input type="text" name="name" placeholder="Enter your name" />
        <button type="submit">Submit</button>
      </form>
    </div>
  )
}

export default Form_Handling


### Two-Way Binding

```js
import React, { useState } from 'react'

const Two_Way_Binding = () => {

  const [title, setTitle] = useState('');

  const submitHandler = (e) => {
    e.preventDefault();
    console.log("Form Submitted By : ", title);

    // Reset the Form after Buttom is pressed
    setTitle('');
  } 
  
  return (
    <div>
      <form onSubmit = {(e) => {
        submitHandler(e);
      }} >
        <input type='text' placeholder='Enter Your Name' 
              value={title} 
              onChange={(e) => setTitle(e.target.value)} />
        <button>Submit</button>
      </form>
    </div>
  )
}

export default Two_Way_Binding


