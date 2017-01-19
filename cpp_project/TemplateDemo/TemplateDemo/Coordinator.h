#include <ostream>

class Coordinator
{
public:
	Coordinator(int x=0, int y=0);
	friend std::ostream& operator<<(std::ostream& out, Coordinator& cood);//two para need to define as a friend function;
private:
	int m_x;
	int m_y;
};

Coordinator::Coordinator(int x, int y)
{
	m_x=x;
	m_y=y;
}
 std::ostream& operator<<(std::ostream& out, Coordinator& cood)
{
	out<<"m_x="<<cood.m_x<<"  "<<"m_y="<<cood.m_y<<std::endl;
	
	return out;

}
