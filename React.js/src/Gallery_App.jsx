import {useEffect, useState} from 'react'
import './Gallery_App.css'

const Gallery_App = () => {

  const [Images, setImages] = useState([])
  const [PageNo, setPageNo] = useState(0);

  const response = async () => {
    const data = await fetch('https://picsum.photos/v2/list?page=2&limit=10')
    console.log(data)
    setImages(await data.json())
  }

  useEffect(() => {
    response();
  },[PageNo])


  return (
    <div className='GalleryApp'>
      <h1>Gallery App</h1>

      <div className='Gallery'>
        {
          Images.map(function(elem,idx){
            return <div key = {idx}>
              <img src={elem.download_url}></img>
              <p>{elem.author}</p>
            </div>
          })
        }
      </div>

      <button>Prev</button>
      <p>Page {PageNo}</p>
      <button>Next</button>
    </div>
  )
}

export default Gallery_App
