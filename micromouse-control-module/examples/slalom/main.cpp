/**
 * @file main.cpp
 * @author Ryotaro Onuki (kerikun11+github@gmail.com)
 * @brief slalom trajectory generation example
 * @date 2020-05-04
 */
#include <ctrl/slalom.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace ctrl;

void printCsv(const std::string &filebase, const slalom::Shape &ss,
              const float th_start = 0)
{
  auto st = slalom::Trajectory(ss);
  const float v = ss.v_ref;
  State s;
  st.reset(v, th_start, ss.straight_prev / v);
  // const float Ts = st.getTimeCurve() * 1e-5f;
  const float Ts = 1e-3f;
  const auto printCSV = [](std::ostream &os, const float t, const State &s)
  {
    os << t;
    os << "," << s.dddq.th;
    os << "," << s.ddq.th;
    os << "," << s.dq.th;
    os << "," << s.q.th;
    os << "," << s.dddq.x;
    os << "," << s.ddq.x;
    os << "," << s.dq.x;
    os << "," << s.q.x;
    os << "," << s.dddq.y;
    os << "," << s.ddq.y;
    os << "," << s.dq.y;
    os << "," << s.q.y;
    os << std::endl;
  };
  std::ofstream of;
  const std::vector<float> ticks = {{
      st.getAccelDesigner().t_0(),
      st.getAccelDesigner().t_1(),
      st.getAccelDesigner().t_2(),
      st.getAccelDesigner().t_3(),
      st.getAccelDesigner().t_3() + ss.straight_post / v,
  }};
  float t = 0;
  for (size_t i = 0; i < ticks.size(); ++i)
  {
    of = std::ofstream(filebase + "_" + std::to_string(i) + ".csv");
    while (t < ticks[i])
      st.update(s, t, Ts, 0), printCSV(of, t, s), t += Ts;
  }
}

int main(void)
{
  static auto ss = slalom::Shape(Pose(90, 90, M_PI / 2), 80, 0, 500 * M_PI, 5 * M_PI, M_PI);
  // static auto ss = slalom::Shape(Pose(45, 45, M_PI / 2), 40);
  // static auto ss = slalom::Shape(Pose(90, 90, M_PI / 2), 75);
  // static auto ss = slalom::Shape(Pose(0, 90, M_PI), 90, 10);
  std::cout << ss;
  const AccelDesigner ad(ss.dddth_max, ss.ddth_max, ss.dth_max, 0, 0,
                         ss.curve.th);
  const auto t_ref = ad.t_end() + ss.straight_post / ss.v_ref;
  std::cout << "\tt_ref:\t" << t_ref << std::endl;
  printCsv("slalom", ss);

  return 0;
}
