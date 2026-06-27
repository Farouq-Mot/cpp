
/*
"When do you need to implement a copy constructor?"

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
Cases where you NEED a copy constructor
The general rule is:

If your class owns a resource, you should think about implementing a copy constructor (or deleting it if copying should not be allowed).

Case	Example	Why?
✅ Dynamic memory	new, new[]	Prevent shallow copy and double deletion
✅ Raw arrays	char*, int*, float*	Need to copy the data, not just the pointer
✅ File handles	FILE*, file descriptors	Two objects should not accidentally manage the same file unless that's your intended design
✅ Socket handles	TCP/UDP sockets	Ownership of the connection must be defined
✅ Camera handles	Camera SDK objects	Avoid two objects trying to close the same camera
✅ GPU memory	cudaMalloc(), OpenCL buffers	Requires explicit resource management
✅ Database connections	Database handles	Copying the handle may not make sense
✅ Mutexes or synchronization objects	pthread_mutex_t, OS handles	Usually cannot or should not be copied
✅ Any custom resource	CAN device, USB device, serial port	Resource owner
*/

/*
You are writing software for a vehicle safety system. A camera/LiDAR module produces a SensorSnapshot. 
Each snapshot contains the class below.
distances_m is a dynamically allocated array containing distance readings in meters.

Your task: implement a proper copy constructor so this code works safely
*/


#include <iostream>

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

int main()
{
    SensorSnapshot original(2, 1719500000, 3);

    original.setDistance(0, 1.5f);
    original.setDistance(1, 2.2f);
    original.setDistance(2, 3.8f);

    SensorSnapshot copy = original;

    original.setDistance(0, 99.0f);

    original.print();
    copy.print();

    return 0;
}