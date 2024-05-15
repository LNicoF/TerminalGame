#pragma once
#include "common.h"
#include "object_itf.h"

interface IPixel : extends IObject {
} ;
SET_IID( IPixel, "86e46913-4ad5-4b37-aa68-a7ad614f5529" ) ;

/**
 * ∀ d ∈ IDisplay
 *
 * d.draw() ;
 * Pre: 0 <= x < d.width ∧ 0 <= y < d.height
 *
 *
 *  With draw() you stage a pixel for drawing
 * and that pixel will be printed (unless overwritten)
 * when refresh() gets called.
 */
interface IDisplay : extends IObject {
    virtual void draw( uint x, uint y, IPixel* pixel ) = 0 ;
    virtual void refresh() = 0 ;
} ;
SET_IID( IDisplay, "2f78636c-8b9d-4638-baf1-1411c9f5c088" ) ;

IDisplay* createDisplay(uint width, uint height) ;
