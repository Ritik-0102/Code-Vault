import { Link , Outlet } from "react-router-dom"

const Collection = () => {
  return (
    <div>
        <div  className='flex gap-10 justify-center px-8 items-center bg-gray-400'>
            <Link to = '/collection/mens' className="text-mist-900 no-underline">Mens</Link>
            <Link to = '/collection/womens' className="text-mist-900 no-underline">Womens</Link>
            <Link to = '/collection/kids' className="text-mist-900 no-underline">Kids</Link>
        </div>
        <Outlet />
    </div>
  )
}

export default Collection
