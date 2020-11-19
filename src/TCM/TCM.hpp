#ifndef TCM_HPP
#define TCM_HPP

#include "frames.hpp"
#include "gearbox.hpp"

namespace fr=frames;

class TCM 
{
  public:
    TCM(){};
    ~TCM() = default;
    void Update(fr::frame_100 &frm_100, fr::frame_200 &frm_200);
    void Write(fr::frame_100 &frm_100, fr::frame_200 &frm_200, fr::frame_300 &frm_300);
  private:
    Gearbox gb;
};

#endif //TCM_HPP