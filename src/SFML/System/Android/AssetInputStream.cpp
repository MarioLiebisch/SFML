////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/AssetInputStream.hpp>
#include <SFML/System/Android/Activity.hpp>
#include <SFML/System/Lock.hpp>

#include <SFML/System/Err.hpp>

namespace sf
{
////////////////////////////////////////////////////////////
AssetInputStream::AssetInputStream() :
m_file (NULL)
{
}

////////////////////////////////////////////////////////////
AssetInputStream::~AssetInputStream()
{
	if (m_file)
		AAsset_close(m_file);
}

////////////////////////////////////////////////////////////
bool AssetInputStream::open(const std::string& filename)
{
    priv::ActivityStates* states = priv::getActivity(NULL);
    Lock(states->mutex);

    if (m_file)
		AAsset_close(m_file);
	
	m_file = AAssetManager_open(states->activity->assetManager, filename.c_str(), AASSET_MODE_UNKNOWN);
    return !!m_file;
}


////////////////////////////////////////////////////////////
Int64 AssetInputStream::read(void* data, Int64 size)
{
    if (m_file)
		return AAsset_read(m_file, data, size);
    return 0;
}


////////////////////////////////////////////////////////////
Int64 AssetInputStream::seek(Int64 position)
{
    if (m_file)
        return AAsset_seek(m_file, position, SEEK_SET);
	return 0;
}


////////////////////////////////////////////////////////////
Int64 AssetInputStream::tell()
{
    if (m_file)
		return getSize() - AAsset_getRemainingLength(m_file);
	return 0;
}


////////////////////////////////////////////////////////////
Int64 AssetInputStream::getSize()
{
    if (m_file)
		return AAsset_getLength(m_file);
	return 0;
}

} // namespace sf
