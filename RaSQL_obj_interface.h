
class RaSQL_obj_interface
{
	public:
		virtual bool RaSQL_Create() = 0;
		virtual bool RaSQL_Drop() = 0;
		virtual bool RaSQL_Use() = 0;
		virtual bool RaSQL_Find() = 0;
}
