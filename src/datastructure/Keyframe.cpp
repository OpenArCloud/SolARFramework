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

#include "datastructure/Keyframe.h"

#include <cstddef> //TO DO: remove with a complete implementation

namespace SolAR {
namespace datastructure {

int Keyframe::m_keyframeIdx = 0;

const std::map<unsigned int, unsigned int>& Keyframe::getNeighborKeyframes()
{
	std::unique_lock<std::mutex> lock(m_mutexNeighbor);
	return m_neighborKeyframes;
}

std::vector<unsigned int> Keyframe::getBestNeighborKeyframes(int nbKeyframes)
{
	std::unique_lock<std::mutex> lock(m_mutexNeighbor);
	std::vector<std::pair<unsigned int, unsigned int>> weightKf;
	for (auto it = m_neighborKeyframes.begin(); it != m_neighborKeyframes.end(); it++)
		weightKf.push_back(std::make_pair(it->second, it->first));
	std::sort(weightKf.begin(), weightKf.end(), std::greater<std::pair<unsigned int, unsigned int>>());
	std::vector<unsigned int> out;
	for (auto it : weightKf) {
		out.push_back(it.second);
		if (out.size() == nbKeyframes)
			break;
	}
	return out;
}

void Keyframe::addNeighborKeyframe(unsigned int idxKeyframe, unsigned int weight)
{
	std::unique_lock<std::mutex> lock(m_mutexNeighbor);
	m_neighborKeyframes[idxKeyframe] = weight;
}

}
}
