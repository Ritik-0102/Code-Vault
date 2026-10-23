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
