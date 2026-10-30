import React, {useState} from 'react'
import axios from 'axios'

const API_Calls = () => {

  const [data, setdata] = useState([])
  const [dataByAxios, setdataByAxios] = useState([])
  
  const response = async () => {
    // Fetching data from API using fetch method
    const res = await fetch('https://jsonplaceholder.typicode.com/users');

    // Parsing the response to JSON and storing it in the data array
    setdata(await res.json());

  }

  // We can also use axios to fetch data from API. First we need to install axios using npm install axios command. Then we can import it and use it to fetch data from API.
  const response2 = async () => {
    const res = await axios.get('https://picsum.photos/v2/list');
    setdataByAxios(res.data);
  }

  return (
    <div>
      <h1>API Calls</h1>

      <button onClick={response}> Get Data</button>
      <button onClick={response2}> Get Data with Axios</button>

      {
        data.map((e, idx) => {
          return <div key={idx}>
            <h4>{idx}  -  {e.name}  -  {e.email}</h4>
          </div>
        })
      }
    
      {
        dataByAxios.map((e, idx) => {
          return <div key={idx}> 
            <h4 style={{alignItems:'self-start'}}>{idx}  -  {e.author}  -  <img style = {{width: '250px', height: '200px', border: '1px solid #ccc' , borderRadius: '15px'}} src={e.download_url} alt={e.url} /></h4>
          </div>
        })
      }

    </div>
  )
}

export default API_Calls
