

class CFizzFuzz
{
public:
	double m_Length{ 1.0 };                // Length of a box in inches
	double m_Width{ 1.0 };                 // Width of a box in inches
	double m_Height{ 1.0 };                // Height of a box in inches

										   // Function to calculate the volume of a box
	double volume()
	{
		return m_Length*m_Width*m_Height;
	}


};
