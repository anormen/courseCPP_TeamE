#ifndef TCM_HPP
#define TCM_HPP

#include "frames.hpp"
#include "gearbox.hpp"

class TCM 
{
  public:
    TCM(){};
    ~TCM() = default;
    void Update(frame_100 &frm_100, frame_200 &frm_200);
    void Write(frame_200 &frm_200, frame_300 &frm_300);
  private:
    Gearbox gb;
};

#endif //TCM_HPP