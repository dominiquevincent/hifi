//
// starfield/renderer/VertexOrder.h
// interface
//
// Created by Tobias Schwinger on 3/22/13.
// Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#ifndef __interface__starfield__renderer__VertexOrder__
#define __interface__starfield__renderer__VertexOrder__

#ifndef __interface__Starfield_impl__
#error "This is an implementation file - not intended for direct inclusion."
#endif

#include "starfield/Config.h"
#include "starfield/data/InputVertex.h"
#include "starfield/renderer/Tiling.h"

namespace starfield {

    /**
     * Defines the vertex order for the renderer as a bit extractor for
     * binary in-place Radix Sort.
     */
    class VertexOrder : public Radix2IntegerScanner<unsigned>
    {
        Tiling _objTiling;

        typedef Radix2IntegerScanner<unsigned> base;
    public:

        explicit VertexOrder(Tiling const& tiling) :

            base(tiling.getTileIndexBits() + BrightnessBits),
            _objTiling(tiling) {
        }

        bool bit(InputVertex const& v, state_type const& s) const {

            // inspect (tile_index, brightness) tuples
            unsigned key = getBrightness(v.getColor()) ^ BrightnessMask;
            key |= _objTiling.getTileIndex(
                    v.getAzimuth(), v.getAltitude()) << BrightnessBits;
            return base::bit(key, s); 
        }
    };

} // anonymous namespace

#endif

