#pragma once

#include <numeric>
#include <algorithm>
#include "../../utility/data.hpp"

namespace hyperpose {

namespace parser {

class pose_proposal {
public:
    pose_proposal(cv::Size net_resolution, float point_thresh = 0.05, float limb_thresh = 0.05, float mns_thresh = 0.3, int max_person = 32)
        :
        m_net_resolution(net_resolution),
        m_point_thresh(point_thresh),
        m_limb_thresh(limb_thresh), m_nms_thresh(mns_thresh),
        m_max_person(max_person) {}

    std::vector<human_t> process(
        const feature_map_t& conf_point, const feature_map_t& conf_iou,
        const feature_map_t& x, const feature_map_t& y, const feature_map_t& w, const feature_map_t& h,
        const feature_map_t& edge);

    inline std::vector<human_t> process(const std::vector<feature_map_t>& feature_map_list) {
        assert(feature_map_list.size() == 7);
        return this->process(feature_map_list[0], feature_map_list[1], feature_map_list[2], feature_map_list[3], feature_map_list[4], feature_map_list[5], feature_map_list[6]);
    }

    void set_point_thresh(float thresh);
    void set_limb_thresh(float thresh);
    void set_nms_thresh(float thresh);
    void set_max_person(int n_person);

private:
    cv::Size m_net_resolution;
    float m_point_thresh;
    float m_limb_thresh;
    float m_nms_thresh;
    int m_max_person;
};

}

} // namespace hyperpose