import { useParams } from 'react-router-dom'

const Dynamic_Routed_Page = () => {

    // This is used to extract parameters whatever is typed in dynamic link
    const params = useParams()

  return (
    <div className='flex h-full items-center justify-center'>
        <h2 className='text-2xl text-lime-400'>
            This is a Dynamically Routed Page for Link : /About/{params.anything}
        </h2>
    </div>
  )
}

export default Dynamic_Routed_Page
