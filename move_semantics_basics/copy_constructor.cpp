
/*
" ================================== When do you need to implement a copy constructor? ================================== "

A strong answer is:

"I implement a copy constructor when my class owns a resource that cannot be safely copied with the 
compiler's default member-wise copy. 
Examples include dynamically allocated memory, file handles, sockets, GPU buffers, or other unique resources.
The default copy constructor copies pointer values rather than the data they point to,
which can lead to shared state, dangling pointers, and double deletion.
If the class only contains value types or RAII types like std::string or std::vector, 
I usually rely on the compiler-generated copy constructor and follow the Rule of Zero."
*/

/*
================================== Interview Rule to Remember ==================================

A concise answer that interviewers like is:

No resource ownership → Let the compiler generate the copy constructor.
Owns dynamic memory or another resource → Write a custom copy constructor (deep copy) or disable copying if sharing that resource is not valid.
Prefer RAII types (std::string, std::vector, smart pointers) → You usually don't need to write a copy constructor yourself 
because these types already implement correct ownership semantics.
*/



/*
==================================   Cases where you NEED a copy constructor  ==================================
The general rule is:

If your class owns a resource, you should think about implementing a copy constructor (or deleting it if copying should not be allowed).

Case	                      Example	                                                 Why?
✅ Dynamic memory	      new, new[]	                                Prevent shallow copy and double deletion
✅ Raw arrays	          char*, int*, float*	                        Need to copy the data, not just the pointer
✅ File handles	          FILE*, file descriptors	                    Two objects should not accidentally manage the same file unless that's your intended design
✅ Socket handles          TCP/UDP sockets          	                    Ownership of the connection must be defined
✅ Camera handles	      Camera SDK objects	                        Avoid two objects trying to close the same camera
✅ GPU memory	          cudaMalloc(), OpenCL buffers	                Requires explicit resource management
✅ Database 
    connections	           Database handles	                              Copying the handle may not make sense
✅ Mutexes or 
   synchronization 
   objects	               pthread_mutex_t, OS handles	                  Usually cannot or should not be copied
✅ Any custom resource	 CAN device, USB device, serial port	         Resource owner must be explicit 
*/


/*
Example practice:
You are writing software for a vehicle safety system. A camera/LiDAR module produces a SensorSnapshot. 
Each snapshot contains the class below.
distances_m is a dynamically allocated array containing distance readings in meters.

Your task: implement a proper copy constructor so this code works safely
*/


#include <iostream>
#include <vector>

/*
class SensorSnapshot
{
private:
    int camera_id;
    long long timestamp_ms;
    int point_count;
    float* distances_m;

public:
    SensorSnapshot(int id, long long ts, int count);

    // TODO: write copy constructor

    ~SensorSnapshot();

    void setDistance(int index, float value);
    float getDistance(int index) const;
    void print() const;
};
*/


class SensorSnapshot
{
private:
    int camera_id;
    long long timestamp_ms;
    int point_count;
    float* distances_m;

public:
    SensorSnapshot(int id, long long ts, int count)
        : camera_id(id),
          timestamp_ms(ts),
          point_count(count),
          distances_m(new float[count])
    {
        for (int i = 0; i < point_count; ++i)
        {
            distances_m[i] = 0.0f;
        }
    }

    // TODO: implement copy constructor here
    SensorSnapshot(const SensorSnapshot& other):
    camera_id(other.camera_id),
    timestamp_ms(other.timestamp_ms),
    point_count(other.point_count),
    distances_m(new float(other.point_count)){
        
        for (int ii=0; ii< other.point_count; ++ii  ){
            distances_m[ii]= other.distances_m[ii];
        }
    }


    ~SensorSnapshot()
    {
       delete[] distances_m;
    }

    void setDistance(int index, float value)
    {
        if (index >= 0 && index < point_count)
        {
            distances_m[index] = value;
        }
    }

    float getDistance(int index) const
    {
        if (index >= 0 && index < point_count)
        {
            return distances_m[index];
        }
        return -1.0f;
    }

    void print() const
    {
        std::cout << "Camera: " << camera_id
                  << ", timestamp: " << timestamp_ms
                  << ", distances: ";

        for (int i = 0; i < point_count; ++i)
        {
            std::cout << distances_m[i] << " ";
        }
        std::cout << std::endl;
    }
};

// ============= using vecotr instead of float pointer to eliminate custom copy constructor and destructor ============
// in this class, I used a vecotr instead of a pointer to float.
// vecotr takes care of copy and move constrcutor and there is not need to implemnte custom copy constructor or 
// and there is no need to delete any thing using the destructor.
class SensorSnapshot_NPointer{

    private:
        int camera_id;
        long long timestamp_ms;
        int point_count;
        std::vector<float> distances_m;
    
    public:
    SensorSnapshot_NPointer(int camera_id, long long timestamp_ms, int point_count ):
    camera_id(camera_id),
    timestamp_ms(timestamp_ms),
    point_count(point_count),
    distances_m(point_count, 0.0f)
    {};


    void setDistance(int index, float dist){

        if (index >=0 && index < point_count)
        {
            distances_m[index]=dist;
        }
        else{

            std::cout << "index out of bound" << std::endl;
        };


    };

    void print_address(){
        std::cout << " Object address " << this << std::endl;
        std::cout << " vecotr first element address " << distances_m.data() << std::endl;
    }


    void print_all(){

        for ( auto const& d : distances_m ){

            std::cout << d << std::endl;
        };
    }






};




int main()
{
    SensorSnapshot original(1, 1719500000, 3);

    original.setDistance(0, 1.5f);
    original.setDistance(1, 2.2f);
    original.setDistance(2, 3.8f);
  

    SensorSnapshot copy = original;

    original.setDistance(0, 99.0f);

    original.print();
    copy.print();

    std:: cout << "========== section for modern class with  no float pointer" << std::endl;

    SensorSnapshot_NPointer  s1_np (2, 2333500000, 2 );
    SensorSnapshot_NPointer  s2_np (3, 3111500000, 3 );

    s1_np.print_address();
    s2_np.print_address();

    s1_np.setDistance(0, 0.1);
    s1_np.setDistance(1, 0.2);
    s1_np.setDistance(2, 0.3);

    s2_np.setDistance(0, 0.7);
    s2_np.setDistance(1, 0.8);
    s2_np.setDistance(2, 0.9);

    s1_np.print_all();
    s2_np.print_all();
    
    
    return 0; 
}