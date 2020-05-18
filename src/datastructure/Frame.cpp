/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "datastructure/Frame.h"
#include "datastructure/Keyframe.h"

namespace SolAR {
namespace datastructure {

Frame::Frame(const SRef<Frame> frame) : m_keypoints(frame->getKeypoints()), m_descriptors(frame->getDescriptors()), m_view(frame->getView()), m_referenceKeyFrame(frame->getReferenceKeyframe()), m_pose(frame->getPose()), m_mapVisibility(frame->getVisibility()){}

Frame::Frame(const SRef<Keyframe> keyframe) : m_keypoints(keyframe->getKeypoints()), m_descriptors(keyframe->getDescriptors()), m_view(keyframe->getView()), m_referenceKeyFrame(keyframe->getReferenceKeyframe()), m_pose(keyframe->getPose()), m_mapVisibility(keyframe->getVisibility()) {
}

Frame::Frame(const std::vector<Keypoint> & keypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view, SRef<Keyframe> refKeyframe, const Transform3Df pose): m_keypoints(keypoints), m_descriptors(descriptors), m_view(view), m_referenceKeyFrame(refKeyframe), m_pose(pose){}

Frame::Frame(const std::vector<Keypoint> & keypoints, const SRef<DescriptorBuffer> descriptors, const SRef<Image> view,  const Transform3Df pose): m_keypoints(keypoints), m_descriptors(descriptors), m_view(view), m_pose(pose){}

SRef<Image>  Frame::getView()
{
    return m_view;
}

Transform3Df Frame::getPose()
{
	std::unique_lock<std::mutex> lock(m_mutexPose);
    return m_pose;
}

void Frame::setPose(const Transform3Df & pose)
{
	std::unique_lock<std::mutex> lock(m_mutexPose);
    m_pose = pose;
}

void Frame::setKeypoints(const std::vector<Keypoint> & kpts){
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
    m_keypoints  = kpts;
}

SRef<DescriptorBuffer> Frame::getDescriptors()
{
	std::unique_lock<std::mutex> lock(m_mutexDescriptors);
    return m_descriptors;
}

void Frame::setDescriptors(SRef<DescriptorBuffer> &descriptors)
{
	std::unique_lock<std::mutex> lock(m_mutexDescriptors);
	m_descriptors = descriptors;
}

const std::map<uint32_t, uint32_t>& Frame::getVisibility()
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	return m_mapVisibility;
}

void Frame::setVisibility(const std::map<uint32_t, uint32_t>& visibilities)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility = visibilities;
}

void Frame::addVisibilities(const std::map<uint32_t, uint32_t>& visibilites)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility.insert(visibilites.begin(), visibilites.end());
}

void Frame::addVisibility(uint32_t id_keypoint, uint32_t id_cloudPoint)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	m_mapVisibility[id_keypoint] = id_cloudPoint;
}

bool Frame::removeVisibility(uint32_t id_keypoint, uint32_t id_cloudPoint)
{
	std::unique_lock<std::mutex> lock(m_mutexVisibility);
	if (m_mapVisibility.find(id_keypoint) == m_mapVisibility.end())
		return false;
	else {
		m_mapVisibility.erase(id_keypoint);
		return true;
	}
}

const std::vector<Keypoint> & Frame::getKeypoints()
{
	std::unique_lock<std::mutex> lock(m_mutexKeypoint);
    return m_keypoints;
}

void Frame::setReferenceKeyframe(SRef<Keyframe> keyframe)
{
	std::unique_lock<std::mutex> lock(m_mutexReferenceKeyframe);
    m_referenceKeyFrame = keyframe;
}

SRef<Keyframe> Frame::getReferenceKeyframe()
{
	std::unique_lock<std::mutex> lock(m_mutexReferenceKeyframe);
    return m_referenceKeyFrame;
}

}
}
