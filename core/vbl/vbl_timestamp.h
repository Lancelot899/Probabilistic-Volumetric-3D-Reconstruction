#ifndef vbl_timestamp_h
#define vbl_timestamp_h

class vbl_timestamp
{
public:

  vbl_timestamp();
  virtual ~vbl_timestamp();
  
  void touch();
  unsigned long get_time_stamp() const { return timestamp_; };
  bool older(vbl_timestamp const& obj) const { return timestamp_ < obj.get_time_stamp(); }

protected:
  unsigned long timestamp_;

private:
  static unsigned long mark;

  static unsigned long get_unique_timestamp();
};

#endif
