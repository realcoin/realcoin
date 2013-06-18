// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 realcoin Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xd6b2bcbb7ce7d97f531c7e9b8cd4360b9d0e552c21ba82862cfe6bb28acd0809"))
            (     1, uint256("0x9f4cb7a5e5b91c948306ad84e2a604fe328fb744c2e802eaa84344a61ee0ba00"))
            (     20, uint256("0xb9c6a17a8a97c2f35add8167ebdec555eae5a066ccab284bfe1e629d6f1aada9"))
            (     100, uint256("0x8715ab51d8d22997f07277c5f6a3cb60ea63ccd70e017b7c1d7c5180520e56c3"))
            (     1080, uint256("0x3ac628565248bbddfb98dcc71e710f7cf634c150ca87c35a99ef42f9a58235d4"))
            (     5000, uint256("0xdfb3f4b4b115b4408df4e1b6b625eb99f83ec050e526248c3fdc978da3b2bca6"))
            (     10000, uint256("0xdc751be1cc08013f1d418095e6a853e1c51bdc7b3c2fec4bea788532bd07903e"))
            (     20000, uint256("0x0ae3e8b453eb3fda766d8fb542d815f45a717dc0c7ab1974d61882413ed429d8"))
            (     30000, uint256("0x595bdfadfba6a96bc8daedad3fdfa0c58b95d73a0203c9600277b87ee614a803"))
            (     38628, uint256("0x297b187c764214c6bf6208941b9a5a7d0f2f8b2730f660800c02a366637db9bd"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
        //return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
        //return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
                //return NULL;
        }
        return NULL;
    }
}
