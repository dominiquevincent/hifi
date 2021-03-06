//
// FieldOfView.h
// interface
//
// Created by Tobias Schwinger on 3/21/13.
// Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#ifndef __interface__FieldOfView__
#define __interface__FieldOfView__

#include <glm/glm.hpp>

// 
// Viewing parameter encapsulation.
// 
class FieldOfView {

        glm::mat4   _matOrientation;
        glm::vec3   _vecBoundsLow;
        glm::vec3   _vecBoundsHigh;
        float       _valWidth;
        float       _valHeight;
        float       _valAngle;
        float       _valZoom;
        int         _enmAspectBalancing;
    public:

        FieldOfView();

        // mutators

        FieldOfView& setBounds(glm::vec3 const& low, glm::vec3 const& high) {
                _vecBoundsLow = low; _vecBoundsHigh = high; return *this; }

        FieldOfView& setOrientation(glm::mat4 const& matrix) { _matOrientation = matrix; return *this; }

        FieldOfView& setPerspective(float angle) { _valAngle = angle; return *this; }

        FieldOfView& setResolution(unsigned width, unsigned height) { _valWidth = width; _valHeight = height; return *this; }

        FieldOfView& setZoom(float factor) { _valZoom = factor; return *this; }

        enum aspect_balancing
        {
            expose_more,
            expose_less,
            stretch
        };

        FieldOfView& setAspectBalancing(aspect_balancing v) { _enmAspectBalancing = v; return *this; }

        // dumb accessors

        glm::mat4 const& getOrientation()    const   { return _matOrientation; }
        float            getWidthInPixels()  const   { return _valWidth; }
        float            getHeightInPixels() const   { return _valHeight; }
        float            getPerspective()    const   { return _valAngle; }

        // matrices

        // 
        // Returns a full transformation matrix to project world coordinates
        // onto the screen.
        // 
        glm::mat4 getWorldScreenXform() const;

        // 
        // Transforms world coordinates to viewer-relative coordinates.
        //
        // This matrix can be used as the modelview matrix in legacy GL code
        // where the projection matrix is kept separately.
        // 
        glm::mat4 getWorldViewerXform() const;

        // 
        // Returns the transformation to of viewer-relative coordinates back
        // to world space. 
        //
        // This matrix can be used to set up a coordinate system for avatar
        // rendering.
        // 
        glm::mat4 getViewerWorldXform() const;

        // 
        // Returns the transformation of viewer-relative coordinates to the
        // screen.
        //
        // This matrix can be used as the projection matrix in legacy GL code.
        // 
        glm::mat4 getViewerScreenXform() const;


        // other useful information

        // 
        // Returns the size of a pixel in world space, that is the minimum
        // in respect to x/y screen directions.
        // 
        float getPixelSize() const;

        // 
        // Returns the frustum as used for the projection matrices.
        // The result depdends on the bounds, eventually aspect correction
        // for the current resolution, the perspective angle (specified in
        // respect to diagonal) and zoom.
        // 
        void getFrustum(glm::vec3& low, glm::vec3& high) const;

        // 
        // Returns the z-offset from the origin to where orientation ia
        // applied.
        // 
        float getTransformOffset() const { return _vecBoundsHigh.z; }

        // 
        // Returns the aspect ratio.
        // 
        float getAspectRatio() const { return _valHeight / _valWidth; }
};

#endif

