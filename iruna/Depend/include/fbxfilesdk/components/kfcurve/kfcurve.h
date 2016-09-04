/*!  \file kfcurve.h
 */

#ifndef FBXFILESDK_COMPONENTS_KFCURVE_KFCURVE_H
#define FBXFILESDK_COMPONENTS_KFCURVE_KFCURVE_H

/**************************************************************************************

 Copyright (C) 2001 - 2010 Autodesk, Inc. and/or its licensors.
 All Rights Reserved.

 The coded instructions, statements, computer programs, and/or related material 
 (collectively the "Data") in these files contain unpublished information 
 proprietary to Autodesk, Inc. and/or its licensors, which is protected by 
 Canada and United States of America federal copyright law and by international 
 treaties. 
 
 The Data may not be disclosed or distributed to third parties, in whole or in
 part, without the prior written consent of Autodesk, Inc. ("Autodesk").

 THE DATA IS PROVIDED "AS IS" AND WITHOUT WARRANTY.
 ALL WARRANTIES ARE EXPRESSLY EXCLUDED AND DISCLAIMED. AUTODESK MAKES NO
 WARRANTY OF ANY KIND WITH RESPECT TO THE DATA, EXPRESS, IMPLIED OR ARISING
 BY CUSTOM OR TRADE USAGE, AND DISCLAIMS ANY IMPLIED WARRANTIES OF TITLE, 
 NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OR USE. 
 WITHOUT LIMITING THE FOREGOING, AUTODESK DOES NOT WARRANT THAT THE OPERATION
 OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE. 
 
 IN NO EVENT SHALL AUTODESK, ITS AFFILIATES, PARENT COMPANIES, LICENSORS
 OR SUPPLIERS ("AUTODESK GROUP") BE LIABLE FOR ANY LOSSES, DAMAGES OR EXPENSES
 OF ANY KIND (INCLUDING WITHOUT LIMITATION PUNITIVE OR MULTIPLE DAMAGES OR OTHER
 SPECIAL, DIRECT, INDIRECT, EXEMPLARY, INCIDENTAL, LOSS OF PROFITS, REVENUE
 OR DATA, COST OF COVER OR CONSEQUENTIAL LOSSES OR DAMAGES OF ANY KIND),
 HOWEVER CAUSED, AND REGARDLESS OF THE THEORY OF LIABILITY, WHETHER DERIVED
 FROM CONTRACT, TORT (INCLUDING, BUT NOT LIMITED TO, NEGLIGENCE), OR OTHERWISE,
 ARISING OUT OF OR RELATING TO THE DATA OR ITS USE OR ANY OTHER PERFORMANCE,
 WHETHER OR NOT AUTODESK HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH LOSS
 OR DAMAGE. 

**************************************************************************************/
#include <fbxfilesdk/fbxfilesdk_def.h>

#include <fbxfilesdk/components/kbaselib/klib/karrayul.h>
#include <fbxfilesdk/components/kbaselib/klib/ktime.h>
#include <fbxfilesdk/components/kbaselib/klib/kdebug.h>
#include <fbxfilesdk/components/kbaselib/object/e/keventbase.h>

#undef  KFBX_FCURVE_INLINE
#define KFBX_FCURVE_INLINE inline

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

KFBX_FORWARD(KFbx);
KFBX_FORWARD(KDataType);
KFBX_FORWARD(KgeQuaternion);
KFBX_FORWARD(KgeRMatrix);

#define KFCURVE_FLOAT
#ifdef KFCURVE_FLOAT
	typedef float kFCurveDouble;
#else
	typedef double kFCurveDouble;
#endif


KFBX_FORWARD(KFCurve);

#define IKFCurveID 43763635

typedef HKFCurve HIKFCurve;
typedef class KFBX_DLL KArrayTemplate< KFCurve * > KArrayKFCurve;

// Recording memory functions declaration
KFBX_DLL kULong GetRecordingMemory();
KFBX_DLL void WatchFree(void* pPtr, kULong pSize);
KFBX_DLL void* WatchMalloc(kULong pSize);

/** Key interpolation type.
* - \e KFCURVE_INTERPOLATION_CONSTANT  Constant value until next key.
* - \e KFCURVE_INTERPOLATION_LINEAR    Linear progression to next key.
* - \e KFCURVE_INTERPOLATION_CUBIC     Cubic progression to next key.
* - \e KFCURVE_INTERPOLATION_ALL
* - \e KFCURVE_INTERPOLATION_COUNT
*/
enum
{
	KFCURVE_INTERPOLATION_CONSTANT    = 0x00000002,		
	KFCURVE_INTERPOLATION_LINEAR	  = 0x00000004,		
	KFCURVE_INTERPOLATION_CUBIC		  = 0x00000008,		
	KFCURVE_INTERPOLATION_ALL		  =	KFCURVE_INTERPOLATION_CONSTANT|KFCURVE_INTERPOLATION_LINEAR|KFCURVE_INTERPOLATION_CUBIC,
	KFCURVE_INTERPOLATION_COUNT		  = 3
};												  

/** Key constant mode.
* - \e KFCURVE_CONSTANT_STANDARD 
* - \e KFCURVE_CONSTANT_NEXT    
* - \e KFCURVE_CONSTANT_ALL    
* - \e KFCURVE_CONSTANT_COUNT
*/
enum
{
	KFCURVE_CONSTANT_STANDARD		  =	0x00000000,
	KFCURVE_CONSTANT_NEXT			  =	0x00000100,
	KFCURVE_CONSTANT_ALL			  =	KFCURVE_CONSTANT_STANDARD | KFCURVE_CONSTANT_NEXT,
	KFCURVE_CONSTANT_COUNT			  = 2
};

/** Key tangent mode for cubic interpolation.
* - \e KFCURVE_TANGEANT_AUTO                Spline cardinal.
* - \e KFCURVE_TANGEANT_TCB                 Spline TCB.
* - \e KFCURVE_TANGEANT_USER                Next slope at the left equal to slope at the right.
* - \e KFCURVE_GENERIC_BREAK                Independent left and right slopes.
* - \e KFCURVE_GENERIC_CLAMP                Auto key should be flat if next or previous keys have same value.
* - \e KFCURVE_GENERIC_TIME_INDEPENDENT     Auto key time independent.
* - \e KFCURVE_TANGEANT_BREAK
* - \e KFCURVE_TANGEANT_AUTO_BREAK
* - \e KFCURVE_TANGEANT_ALL
* - \e KFCURVE_TANGEANT_TYPE_MASK
* - \e KFCURVE_TANGEANT_OVERRIDES_MASK
*/
enum
{
	KFCURVE_TANGEANT_AUTO			  =	0x00000100, 	
	KFCURVE_TANGEANT_TCB			  =	0x00000200,		
	KFCURVE_TANGEANT_USER			  =	0x00000400, 	
	KFCURVE_GENERIC_BREAK			  =	0x00000800, 	
    KFCURVE_GENERIC_CLAMP			  =	0x00001000, 
    KFCURVE_GENERIC_TIME_INDEPENDENT  = 0x00002000,
	KFCURVE_TANGEANT_BREAK			  = KFCURVE_TANGEANT_USER|KFCURVE_GENERIC_BREAK,
	KFCURVE_TANGEANT_AUTO_BREAK	      = KFCURVE_TANGEANT_AUTO|KFCURVE_GENERIC_BREAK,
    KFCURVE_TANGEANT_ALL			  = KFCURVE_TANGEANT_AUTO|KFCURVE_TANGEANT_TCB|KFCURVE_TANGEANT_USER|KFCURVE_GENERIC_BREAK|KFCURVE_GENERIC_CLAMP|KFCURVE_GENERIC_TIME_INDEPENDENT,
    KFCURVE_TANGEANT_TYPE_MASK 		  = KFCURVE_TANGEANT_AUTO|KFCURVE_TANGEANT_TCB|KFCURVE_TANGEANT_USER|KFCURVE_TANGEANT_BREAK,
	KFCURVE_TANGEANT_OVERRIDES_MASK   = KFCURVE_GENERIC_CLAMP|KFCURVE_GENERIC_TIME_INDEPENDENT
};

/** Selection mode.
* - \e KFCURVE_SELECT_POINT 
* - \e KFCURVE_SELECT_LEFT    
* - \e KFCURVE_SELECT_RIGHT    
* - \e KFCURVE_SELECT_ALL
*/
enum 
{
	KFCURVE_SELECT_POINT			  =	0x00010000, 
	KFCURVE_SELECT_LEFT				  =	0x00020000, 
	KFCURVE_SELECT_RIGHT			  =	0x00040000, 
	KFCURVE_SELECT_ALL				  =	KFCURVE_SELECT_POINT|KFCURVE_SELECT_LEFT|KFCURVE_SELECT_RIGHT
};

/** Manipulation flag.
* - \e KFCURVE_MARKED_FOR_MANIP 
* - \e KFCURVE_MARKED_ALL    
*/
enum
{
	KFCURVE_MARKED_FOR_MANIP          = 0x00080000,
	KFCURVE_MARKED_ALL                = KFCURVE_MARKED_FOR_MANIP
};

/** Tangent visibility.
* - \e KFCURVE_TANGEANT_SHOW_NONE 
* - \e KFCURVE_TANGEANT_SHOW_LEFT    
* - \e KFCURVE_TANGEANT_SHOW_RIGHT    
* - \e KFCURVE_TANGEANT_SHOW_BOTH
*/
enum 
{
	KFCURVE_TANGEANT_SHOW_NONE		  = 0x00000000, 
	KFCURVE_TANGEANT_SHOW_LEFT		  = 0x00100000, 
	KFCURVE_TANGEANT_SHOW_RIGHT		  = 0x00200000, 
	KFCURVE_TANGEANT_SHOW_BOTH		  = KFCURVE_TANGEANT_SHOW_LEFT|KFCURVE_TANGEANT_SHOW_RIGHT
};

/** Continuity flag.
* - \e KFCURVE_CONTINUITY 
* - \e KFCURVE_CONTINUITY_FLAT    
* - \e KFCURVE_CONTINUITY_BREAK    
* - \e KFCURVE_CONTINUITY_INSERT    Used to prevent the curve shape from changing when inserting a key
*/
enum
{
    KFCURVE_CONTINUITY				  = 0x00000000,
    KFCURVE_CONTINUITY_FLAT           = 0x00100000,
    KFCURVE_CONTINUITY_BREAK          = 0x00200000,
    KFCURVE_CONTINUITY_INSERT         = 0x00400000  
};

/** Weighted mode.
* - \e KFCURVE_WEIGHTED_NONE 
* - \e KFCURVE_WEIGHTED_RIGHT    
* - \e KFCURVE_WEIGHTED_NEXT_LEFT    
* - \e KFCURVE_WEIGHTED_ALL
*/
enum 
{
	KFCURVE_WEIGHTED_NONE			  =	0x00000000, 
	KFCURVE_WEIGHTED_RIGHT			  =	0x01000000, 
	KFCURVE_WEIGHTED_NEXT_LEFT		  =	0x02000000, 
	KFCURVE_WEIGHTED_ALL			  =	KFCURVE_WEIGHTED_RIGHT|KFCURVE_WEIGHTED_NEXT_LEFT
};

/** Velocity mode.
* - \e KFCURVE_VELOCITY_NONE 
* - \e KFCURVE_VELOCITY_RIGHT    
* - \e KFCURVE_VELOCITY_NEXT_LEFT    
* - \e KFCURVE_VELOCITY_ALL
*/
enum
{
	KFCURVE_VELOCITY_NONE			  = 0x00000000,
	KFCURVE_VELOCITY_RIGHT			  = 0x10000000,
	KFCURVE_VELOCITY_NEXT_LEFT		  = 0x20000000,
	KFCURVE_VELOCITY_ALL			  = KFCURVE_VELOCITY_RIGHT | KFCURVE_VELOCITY_NEXT_LEFT
};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

#define KFCURVE_WEIGHT_DIVIDER       9999       // precise enough and can be divided by 3 without error
#define KFCURVE_DEFAULT_WEIGHT       ((kFCurveDouble)(1.0/3.0))
#define KFCURVE_MIN_WEIGHT           ((kFCurveDouble)(1.0/KFCURVE_WEIGHT_DIVIDER))
#define KFCURVE_MAX_WEIGHT           ((kFCurveDouble)0.99)
#define KFCURVE_DEFAULT_VELOCITY	 0.0 

#endif // DOXYGEN_SHOULD_SKIP_THIS


/** KFCurveKey data indices for cubic interpolation tangent information.
*   User and Break tangent mode (data are doubles).
* - \e KFCURVEKEY_RIGHT_SLOPE 
* - \e KFCURVEKEY_NEXT_LEFT_SLOPE 
*
*   User and Break tangent break mode (data are kInt16 tokens from weight and converted to doubles).
* - \e KFCURVEKEY_WEIGHTS    
* - \e KFCURVEKEY_RIGHT_WEIGHT
* - \e KFCURVEKEY_NEXT_LEFT_WEIGHT
*
*   Velocity mode
* - \e KFCURVEKEY_VELOCITY    
* - \e KFCURVEKEY_RIGHT_VELOCITY    
* - \e KFCURVEKEY_NEXT_LEFT_VELOCITY
*
*   TCB tangent mode (data are floats).
* - \e KFCURVEKEY_TCB_TENSION    
* - \e KFCURVEKEY_TCB_CONTINUITY    
* - \e KFCURVEKEY_TCB_BIAS
*
* - \e KFCURVEKEY_RIGHT_AUTO    
* - \e KFCURVEKEY_NEXT_LEFT_AUTO
*/
enum EKFCurveDataIndex
{
	// User and Break tangent mode (data are doubles).
	KFCURVEKEY_RIGHT_SLOPE			= 0, 
	KFCURVEKEY_NEXT_LEFT_SLOPE		= 1, 

	// User and Break tangent break mode (data are kInt16 tokens from weight and converted to doubles).
	KFCURVEKEY_WEIGHTS				= 2, 
	KFCURVEKEY_RIGHT_WEIGHT			= 2, 
	KFCURVEKEY_NEXT_LEFT_WEIGHT		= 3, 

	// Velocity mode
	KFCURVEKEY_VELOCITY				= 4,
	KFCURVEKEY_RIGHT_VELOCITY		= 4,
	KFCURVEKEY_NEXT_LEFT_VELOCITY	= 5, 

	// TCB tangent mode (data are floats).
	KFCURVEKEY_TCB_TENSION			= 0, 
	KFCURVEKEY_TCB_CONTINUITY		= 1, 
	KFCURVEKEY_TCB_BIAS				= 2,

	KFCURVEKEY_RIGHT_AUTO			= 0,
	KFCURVEKEY_NEXT_LEFT_AUTO		= 1
};

/** Extrapolation mode for function curve extremities.
* - \e KFCURVE_EXTRAPOLATION_CONST 
* - \e KFCURVE_EXTRAPOLATION_REPETITION    
* - \e KFCURVE_EXTRAPOLATION_MIRROR_REPETITION    
* - \e KFCURVE_EXTRAPOLATION_KEEP_SLOPE
*/
enum 
{
	KFCURVE_EXTRAPOLATION_CONST				= 1, 
	KFCURVE_EXTRAPOLATION_REPETITION		= 2, 
	KFCURVE_EXTRAPOLATION_MIRROR_REPETITION	= 3, 
	KFCURVE_EXTRAPOLATION_KEEP_SLOPE		= 4
};

enum 
{
	KFCURVE_BEZIER	= 0, 
	KFCURVE_SAMPLE	= 1, 
	KFCURVE_ISO		= 2
};

typedef kUInt kFCurveInterpolation;
typedef kUInt kFCurveConstantMode;
typedef kUInt kFCurveTangeantMode;
typedef kUInt kFCurveTangeantWeightMode;
typedef kUInt kFCurveTangeantVelocityMode;
typedef kUInt kFCurveExtrapolationMode;
typedef kUInt kFCurveTangeantVisibility;
typedef int kFCurveIndex;

/** Curve event type.
* - \e KFCURVEEVENT_NONE		    default event value
* - \e KFCURVEEVENT_CANDIDATE	    curve value (not candidate) changed
* - \e KFCURVEEVENT_UNUSED1    
* - \e KFCURVEEVENT_UNUSED2    
* - \e KFCURVEEVENT_UNUSED3    
* - \e KFCURVEEVENT_KEY		        key changed (add, removed, edited); see bits 11-15 for precisions
* - \e KFCURVEEVENT_DEPRECATED5 
* - \e KFCURVEEVENT_UNUSED6    
* - \e KFCURVEEVENT_UNUSED7    
* - \e KFCURVEEVENT_SELECTION	    key selection changed
* - \e KFCURVEEVENT_DESTROY	        fcurve destruction
* - \e KFCURVEEVENT_DEPRECATED10
* - \e KFCURVEEVENT_KEYADD    
* - \e KFCURVEEVENT_KEYREMOVE  
* - \e KFCURVEEVENT_EDITVALUE  
* - \e KFCURVEEVENT_EDITTIME   
* - \e KFCURVEEVENT_EDITOTHER  
*/
enum 
{
    KFCURVEEVENT_NONE		=0, // default event value
    KFCURVEEVENT_CANDIDATE	=1 << 0, // curve value (not candidate) changed
    KFCURVEEVENT_UNUSED1    =1 << 1,
    KFCURVEEVENT_UNUSED2    =1 << 2,
    KFCURVEEVENT_UNUSED3    =1 << 3,
    KFCURVEEVENT_KEY		=1 << 4, // key changed (add, removed, edited); see bits 11-15 for precisions
    KFCURVEEVENT_DEPRECATED5 =1 << 5,
    KFCURVEEVENT_UNUSED6    =1 << 6,
    KFCURVEEVENT_UNUSED7    =1 << 7,
    KFCURVEEVENT_SELECTION	=1 << 8, // key selection changed
    KFCURVEEVENT_DESTROY	=1 << 9, // fcurve destruction
    KFCURVEEVENT_DEPRECATED10 =1 << 10,
    KFCURVEEVENT_KEYADD     =1 << 11,
    KFCURVEEVENT_KEYREMOVE  =1 << 12,
    KFCURVEEVENT_EDITVALUE  =1 << 13,
    KFCURVEEVENT_EDITTIME   =1 << 14,
    KFCURVEEVENT_EDITOTHER  =1 << 15,
};


/** Curve event class.
  */
class KFBX_DLL KFCurveEvent : public KEventBase
{
public:
	// Curve event type, the enum stated above allow composition of type (bitfield). 
	// Stored in mType
	
	int mKeyIndexStart; //! Start key index.

	int mKeyIndexStop; 	//!	Stop key index.

	int mEventCount;	//! Count of events.

	/** Clear curve event.
	  */
    KFBX_FCURVE_INLINE void Clear (); 
	
	/** Add a curve event of type pWhat to a curve event object.
	  * \param pWhat
	  * \param pIndex
	  */
    KFBX_FCURVE_INLINE void Add (int pWhat, int pIndex);
};

typedef void (*kFCurveCallback) (KFCurve *pFCurve, KFCurveEvent *FCurveEvent, void* pObject);

/** Defines a tangent derivative and weight
*	\remarks Implementation was made for performance.
* \nosubgrouping
*/
class KFBX_DLL KFCurveTangeantInfo 
{
public:
	KFBX_FCURVE_INLINE KFCurveTangeantInfo();

	kFCurveDouble mDerivative;
	kFCurveDouble mWeight;
	kFCurveDouble mVelocity;
	kFCurveDouble mAuto;  // The auto parameter!
	bool         mWeighted;
	bool		  mHasVelocity;
};

class KFCurveKey;

/**
* class KFCurveKeyAttrManager: Memory manager for KFCurveKey attributes.
*/
class KFCurveKeyAttrManager;


/**
* class KMemoryBlockQueue: Memory queue for KFCurveKey attributes.
*/
class KFBX_DLL KMemoryBlockQueue;

/**
* KPriFCurveKeyAttr stores the additional attributes for KFCurveKey. For most motion capture curves,
* all the keys will have default attribute values. It is no necessary
* to store those default value for each key. See KFCurveKey for all function 
* documentation.
*/
struct KPriFCurveKeyAttr
{
    KPriFCurveKeyAttr() : mFlags(0) {}

	KFBX_FCURVE_INLINE void Set 
		(
		kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
		kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
		kFCurveDouble pData0 = 0.0,
		kFCurveDouble pData1 = 0.0,
		kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
		kFCurveDouble pWeight0   = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pWeight1   = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
		kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
		);

	KFBX_FCURVE_INLINE void SetTCB (float pData0 = 0.0f, float pData1 = 0.0f, float pData2 = 0.0f);
	KFBX_FCURVE_INLINE void Set(KFCurveKey& pSource);
	KFBX_FCURVE_INLINE kFCurveInterpolation GetInterpolation() const;
	KFBX_FCURVE_INLINE void SetInterpolation(kFCurveInterpolation pInterpolation);
	KFBX_FCURVE_INLINE kFCurveConstantMode GetConstantMode() const;
	KFBX_FCURVE_INLINE kFCurveTangeantMode GetTangeantMode( bool pIncludeOverrides = false ) const;
	KFBX_FCURVE_INLINE kFCurveTangeantWeightMode GetTangeantWeightMode() const;
	KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode GetTangeantVelocityMode() const;
	KFBX_FCURVE_INLINE void SetConstantMode(kFCurveConstantMode pMode);
	KFBX_FCURVE_INLINE void SetTangeantMode(kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);
	KFBX_FCURVE_INLINE void SetTangeantWeightMode(kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );
	KFBX_FCURVE_INLINE void SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight );
	KFBX_FCURVE_INLINE void SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );
	KFBX_FCURVE_INLINE kFCurveDouble GetDataDouble(EKFCurveDataIndex pIndex) const;
	KFBX_FCURVE_INLINE void SetDataDouble(EKFCurveDataIndex pIndex, kFCurveDouble pValue);
	KFBX_FCURVE_INLINE float GetDataFloat(EKFCurveDataIndex pIndex) const;
	KFBX_FCURVE_INLINE void SetDataFloat(EKFCurveDataIndex pIndex, float pValue);
	KFBX_FCURVE_INLINE float* GetDataPtr() const;
	KFBX_FCURVE_INLINE void SetSelected(bool pSelected);	
	KFBX_FCURVE_INLINE bool GetSelected() const;
	KFBX_FCURVE_INLINE void SetMarkedForManipulation(bool pMark);	
	KFBX_FCURVE_INLINE bool GetMarkedForManipulation() const;
	KFBX_FCURVE_INLINE void	SetTangeantVisibility (kFCurveTangeantVisibility pVisibility);	
	KFBX_FCURVE_INLINE kFCurveTangeantVisibility GetTangeantVisibility () const;
	KFBX_FCURVE_INLINE void SetBreak(bool pVal); 
	KFBX_FCURVE_INLINE bool GetBreak() const; 
	KFBX_FCURVE_INLINE bool IsEqual(const KPriFCurveKeyAttr& pRsh) const;
	KFBX_FCURVE_INLINE void IncRefCount();
	KFBX_FCURVE_INLINE void DecRefCount();
	KFBX_FCURVE_INLINE kUInt32 GetRefCount() const;

    kUInt32 mFlags;
#ifdef KFCURVE_FLOAT
	float  mData[4];
#else 
	double	mData[2];
	kInt16	mWeight[2];
	kInt16	mVelocity[2];
#endif 	
	kUInt32 mRefCount;

};

/**
* KPriFCurveKey is used as the internal storage format for motion data, 
* We need to make its size as small as possible. so carefully play with
* the pack, alignment for VC,GCC on 32/64-bit OS.
*/
struct KPriFCurveKey
{
	KPriFCurveKey()
	{
		Init();
	}

	KFBX_FCURVE_INLINE void Init();
	KFBX_FCURVE_INLINE void Set (KTime pTime, kFCurveDouble pValue);
	KFBX_FCURVE_INLINE kFCurveDouble GetValue() const;
	KFBX_FCURVE_INLINE void SetValue(kFCurveDouble pValue);
	KFBX_FCURVE_INLINE void IncValue(kFCurveDouble pValue);
	KFBX_FCURVE_INLINE void MultValue(kFCurveDouble pValue);
	KFBX_FCURVE_INLINE KTime GetTime() const;
	KFBX_FCURVE_INLINE void SetTime(KTime pTime);
	KFBX_FCURVE_INLINE void IncTime(KTime pTime);

	KTime mTime;  //8 Bytes
#ifdef KFCURVE_FLOAT
	KPriFCurveKeyAttr* mAttr; // 4 Bytes on 32-bit OS, 8 Bytes on 64-bit OS
	kFCurveDouble mValue; // 4 Bytes (float) for KFCRVE_FLOAT, 8 Bytes (double) otherwise.
#else
	kFCurveDouble mValue;
	KPriFCurveKeyAttr* mAttr;
#endif
};


/** Defines a key within a function curve.
*	\remarks Implementation was made for performance.
*	Keep in mind that there is no check for consistency and memory 
* management ever made throughout the methods' code. This class must be 
* used with a good understanding of its interface.
* Default constructor is used, which does not initialize data 
* member. If an instance has to be initialized, use function KFCurveKey::Set().
* \nosubgrouping
*/
class KFBX_DLL KFCurveKey 
{
public:
	KFCurveKey()
	{
		Init();
	}

public:
	
	/** Set a key.
	*	Use SetTCB() to set a key with cubic interpolation and TCB tangent type.
	*	\param pTime			Key time.
	*	\param pValue			Key value.
	*	\param pInterpolation	Key interpolation type.	Interpolation types are: 
	*							KFCURVE_INTERPOLATION_CONSTANT, 
	*							KFCURVE_INTERPOLATION_LINEAR,
	*							KFCURVE_INTERPOLATION_CUBIC
	*	\param pTangentMode		Key tangent mode (meaningful for cubic 
	*							interpolation only). Tangent modes are: 
	*							KFCURVE_TANGEANT_AUTO,
	*							KFCURVE_TANGEANT_USER,
	*							KFCURVE_TANGEANT_BREAK
	*	\param pData0			Right slope.
	*	\param pData1			Next left slope.
	*	\param pTangentWeightMode	Weight mode if used
	*								KFCURVE_WEIGHTED_NONE
	*								KFCURVE_WEIGHTED_RIGHT
	*								KFCURVE_WEIGHTED_NEXT_LEFT
	*								KFCURVE_WEIGHTED_ALL
	*	\param pWeight0				Right slope weight.
	*	\param pWeight1				Next left slope weight.
	*	\param pVelocity0			Right velocity.
	*	\param pVelocity1			Next left velocity.
	*/
	KFBX_FCURVE_INLINE void Set 
	(
		KTime pTime, 
		kFCurveDouble pValue, 
		kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
		kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
		kFCurveDouble pData0 = 0.0,
		kFCurveDouble pData1 = 0.0,
		kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
		kFCurveDouble pWeight0                             = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pWeight1                             = KFCURVE_DEFAULT_WEIGHT,
		kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
		kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
	);
	
	/**	Set a key with cubic interpolation, TCB tangent mode.
	*	\param pTime	Key time.
	*	\param pValue	Key value.
	*	\param pData0	Tension.
	*	\param pData1	Continuity.
	*	\param pData2	Bias.
	*/
	KFBX_FCURVE_INLINE void SetTCB 
	(
		KTime pTime, 
		kFCurveDouble pValue, 
		float pData0 = 0.0f, 
		float pData1 = 0.0f, 
		float pData2 = 0.0f
	);
	
	/** Key assignment.
	*	\param pSource	Source key to be copied.
	*/
	KFBX_FCURVE_INLINE void Set(KFCurveKey& pSource);
	
	/** Get key interpolation type.
	*	Interpolation types are: KFCURVE_INTERPOLATION_CONSTANT, 
	*							 KFCURVE_INTERPOLATION_LINEAR,
	*							 KFCURVE_INTERPOLATION_CUBIC
	*/
	KFBX_FCURVE_INLINE kFCurveInterpolation GetInterpolation() const;
	
	/** Set key interpolation type.
	*	\param pInterpolation Key interpolation type.
	*	Interpolation types are: KFCURVE_INTERPOLATION_CONSTANT, 
	*							 KFCURVE_INTERPOLATION_LINEAR,
	*							 KFCURVE_INTERPOLATION_CUBIC
	*/
	KFBX_FCURVE_INLINE void SetInterpolation(kFCurveInterpolation pInterpolation);

	/** Get key constant mode.
	*	Warning: This method is meaningful for constant interpolation only.
	*			 Using this method for non constant interpolated key will return unpredicted value.
	* Constant modes are:		KFCURVE_CONSTANT_STANDARD
	*							KFCURVE_CONSTANT_NEXT
	*	\return Key constant mode.
	*/
	KFBX_FCURVE_INLINE kFCurveConstantMode GetConstantMode() const;

	/** Get key tangent mode.
	*   \param pIncludeOverrides 
	*	Warning: This method is meaningful for cubic interpolation only.
	*			 Using this method for non cubic interpolated key will return unpredicted value.
	*	Tangent modes are: KFCURVE_TANGEANT_AUTO,
	*					   KFCURVE_TANGEANT_AUTO_BREAK
	*					   KFCURVE_TANGEANT_TCB,
	*					   KFCURVE_TANGEANT_USER,
	*					   KFCURVE_TANGEANT_BREAK
	*	\return Key tangent mode.
	*/
	KFBX_FCURVE_INLINE kFCurveTangeantMode GetTangeantMode( bool pIncludeOverrides = false ) const;

	/** Get key tangent weight mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_WEIGHTED_NONE,
	*								KFCURVE_WEIGHTED_RIGHT,
	*								KFCURVE_WEIGHTED_NEXT_LEFT,
	*								KFCURVE_WEIGHTED_ALL
	*/
	KFBX_FCURVE_INLINE kFCurveTangeantWeightMode GetTangeantWeightMode() const;

	/** Get key tangent velocity mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_VELOCITY_NONE,
	*								KFCURVE_VELOCITY_RIGHT,
	*								KFCURVE_VELOCITY_NEXT_LEFT,
	*								KFCURVE_VELOCITY_ALL
	*/
	KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode GetTangeantVelocityMode() const;

	/** Set key constant mode.
	*	Warning: This method is meaningful for constant interpolation only.
	*	\param pMode Key constant mode.
	*	Constant modes are:		KFCURVE_CONSTANT_STANDARD
	*							KFCURVE_CONSTANT_NEXT
	*/
	KFBX_FCURVE_INLINE void SetConstantMode(kFCurveConstantMode pMode);

	/** Set key tangent mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pTangent Key tangent mode.
	*	Tangent modes are: KFCURVE_TANGEANT_AUTO,
	*					   KFCURVE_TANGEANT_AUTO_BREAK
	*					   KFCURVE_TANGEANT_TCB,
	*					   KFCURVE_TANGEANT_USER,
	* 				   KFCURVE_TANGEANT_BREAK
	* \param pIgnoreAutoTimeIndepedentConversion \b true ignore the auto time independent conversion flag.
	*/
	KFBX_FCURVE_INLINE void SetTangeantMode(kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);
		
	/** Set key tangent weight mode as double value (cubic interpolation, non TCB tangent mode).
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pTangentWeightMode	Weight mode
	*								KFCURVE_WEIGHTED_NONE
	*								KFCURVE_WEIGHTED_RIGHT
	*								KFCURVE_WEIGHTED_NEXT_LEFT
	*								KFCURVE_WEIGHTED_ALL
	*	\param pMask				Used to select the affected tangents
	*								KFCURVE_WEIGHTED_RIGHT
	*								KFCURVE_WEIGHTED_NEXT_LEFT
	*								KFCURVE_WEIGHTED_ALL
	*/

	KFBX_FCURVE_INLINE void SetTangeantWeightMode(kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );

	/** Set key tangent velocity mode as double value (cubic interpolation, non TCB tangent mode).
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pTangentVelocityMode	Weight mode
	*								KFCURVE_VELOCITY_NONE
	*								KFCURVE_VELOCITY_RIGHT
	*								KFCURVE_VELOCITY_NEXT_LEFT
	*								KFCURVE_VELOCITY_ALL
	*	\param pMask				Used to select the affected tangents
	*								KFCURVE_VELOCITY_RIGHT
	*								KFCURVE_VELOCITY_NEXT_LEFT
	*								KFCURVE_VELOCITY_ALL
	*/

	KFBX_FCURVE_INLINE void SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );

	/** Adjust the actual tangent of the key so that the tangent control point (tangent extremity) 
	*   stays closer to where it should be. This is required because the weight value gets imprecise
	*   when it is small (it is stored as a fixed point value). This method must be called when 
	*   setting the weight coming from a source where the precision is the same. It must be called 
	*   after the tangent value has been set. 
    *   Warning: Do not use this call repetitively (from an interactive editor for example) because 
	*   this function will create imprecision on the tangent value.
	*   \param pIndex FCurveDataIndex
	*								KFCURVEKEY_RIGHT_SLOPE
	*								KFCURVEKEY_NEXT_LEFT_SLOPE
	*								KFCURVEKEY_WEIGHTS
	*								KFCURVEKEY_RIGHT_WEIGHT
	*								KFCURVEKEY_NEXT_LEFT_WEIGHT
	*								KFCURVEKEY_VELOCITY
	*								KFCURVEKEY_RIGHT_VELOCITY
	*								KFCURVEKEY_NEXT_LEFT_VELOCITY
	*								KFCURVEKEY_TCB_TENSION
	*								KFCURVEKEY_TCB_CONTINUITY
	*								KFCURVEKEY_TCB_BIAS
	*								KFCURVEKEY_RIGHT_AUTO
	*								KFCURVEKEY_NEXT_LEFT_AUTO
	*   \param pWeight New tangent weight value.
	*/
	KFBX_FCURVE_INLINE void SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight );


	/** Get key data as double value (cubic interpolation, non TCB tangent mode).
	*	Warning: Using this method for other than cubic interpolated 
	*			 key (linear, constant) will return unpredicted values.
	*	Warning: Slope data is inconsistent for automatic tangent mode.
	*			 Use KFCurve::EvaluateLeftDerivative() and 
	*			 KFCurve::EvaluateRightDerivative() to find
	*			 slope values.
	*	Warning: Using this method for TCB tangent mode key will return 
	*			 unpredicted values. Use KFCurve::GetDataFloat() instead.
	*	\param pIndex Data index, either	KFCURVEKEY_RIGHT_SLOPE,
	*										KFCURVEKEY_NEXT_LEFT_SLOPE.
	*										KFCURVEKEY_NEXT_RIGHT_WEIGHT.
	*										KFCURVEKEY_NEXT_LEFT_WEIGHT
	*/
	KFBX_FCURVE_INLINE kFCurveDouble GetDataDouble(EKFCurveDataIndex pIndex) const;
	
	/**	Set data as double value (cubic interpolation, non TCB tangent mode).
	*	Warning: Using this method for other than cubic interpolated 
	*			 key (linear, constant) is irrelevant.
	*	Warning: Slope data is inconsistent for automatic tangent mode.
	*			 Therefore, it is irrelevant to use this method on automatic 
	*			 tangent mode keys.
	*	Warning: Using this method for a TCB tangent mode key will result
	*			 in unpredictable curve behavior for this key. Use KFCurve::SetDataFloat() 
	*			 instead.
	*	\param pIndex Data index, either	KFCURVEKEY_RIGHT_SLOPE,
	*										KFCURVEKEY_NEXT_LEFT_SLOPE.
	*										KFCURVEKEY_NEXT_RIGHT_WEIGHT.
	*										KFCURVEKEY_NEXT_LEFT_WEIGHT
	*	\param pValue	The data value to set (a slope or a weight).
	*/
	KFBX_FCURVE_INLINE void SetDataDouble(EKFCurveDataIndex pIndex, kFCurveDouble pValue);
	
	/** Get key data as float value (cubic interpolation, TCB tangent mode).
	*	Warning: Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredicted values.
	*	\param pIndex	Data index, either KFCURVEKEY_TCB_TENSION, KFCURVEKEY_TCB_CONTINUITY or KFCURVEKEY_TCB_BIAS.
	*/	
	KFBX_FCURVE_INLINE float GetDataFloat(EKFCurveDataIndex pIndex) const;

	/**	Set data as float value (cubic interpolation, TCB tangent mode).
	*	Warning: Using this method for any key but a cubic interpolated,
	*			 in TCB tangent mode, will return unpredicted values.
	*	\param pIndex	Data index, either KFCURVEKEY_TCB_TENSION, KFCURVEKEY_TCB_CONTINUITY or KFCURVEKEY_TCB_BIAS.
	*	\param pValue	The data value to set.
	*/
	KFBX_FCURVE_INLINE void SetDataFloat(EKFCurveDataIndex pIndex, float pValue);

	/**	Get key data as a pointer
	*	Warning: not supported in 'double' mode.
	*/
	KFBX_FCURVE_INLINE float* GetDataPtr() const;

	//!	Get key value.
	KFBX_FCURVE_INLINE kFCurveDouble GetValue() const;

	/** Set key value.
	  * \param pValue Key value to set.
	  */
	KFBX_FCURVE_INLINE void SetValue(kFCurveDouble pValue);

	/** Increment key value.
	*	\param pValue Value by which key value is incremented.
	*/
	KFBX_FCURVE_INLINE void IncValue(kFCurveDouble pValue);

	/** Multiply key value.
	*	\param pValue Value by which the key value is multiplied.
	*/
	KFBX_FCURVE_INLINE void MultValue(kFCurveDouble pValue);

	/** Get key time
	*	\return Key time (time at which this key is occurring).
	*/
	KFBX_FCURVE_INLINE KTime GetTime() const;

	/** Set key time.
	*	\param pTime Key time (time at which this key is occurring).
	*/
	KFBX_FCURVE_INLINE void SetTime(KTime pTime);

	/** Increment key time.
	*	\param pTime Time value by which the key time is incremented.
	*/
	KFBX_FCURVE_INLINE void IncTime(KTime pTime);

	/** Set if key is currently selected.
	*	\param pSelected Selection flag.
	*/
	KFBX_FCURVE_INLINE void SetSelected(bool pSelected);	

	/** Return if key is currently selected.
	*	\return Selection flag.
	*/
	KFBX_FCURVE_INLINE bool GetSelected() const;

	/** Set if key is currently marked for manipulation.
	*	\param pMark Mark flag.
	*/
	KFBX_FCURVE_INLINE void SetMarkedForManipulation(bool pMark);	

	/** Return if key is currently marked for manipulation.
	*	\return Mark flag.
	*/
	KFBX_FCURVE_INLINE bool GetMarkedForManipulation() const;

	/** Set tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pVisibility	Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*						          KFCURVE_TANGEANT_SHOW_LEFT
	*						          KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	KFBX_FCURVE_INLINE void	SetTangeantVisibility (kFCurveTangeantVisibility pVisibility);	

	/** Return tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\return Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*			                      KFCURVE_TANGEANT_SHOW_LEFT
	*			                      KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	KFBX_FCURVE_INLINE kFCurveTangeantVisibility GetTangeantVisibility () const;

	/** Set/Unset Break tangent
	* Only valid for User and Auto keys
	* \param pVal The break flag.
	*/
	KFBX_FCURVE_INLINE void SetBreak(bool pVal); 

	/** Get if tangent is break
	* Only valid for User and Auto keys
	*/
	KFBX_FCURVE_INLINE bool GetBreak() const; 

	/** Initialize key
	*/
	KFBX_FCURVE_INLINE void Init();


///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//	Anything beyond these lines may not be documented accurately and is 
// 	subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////


	#ifndef DOXYGEN_SHOULD_SKIP_THIS
private:
	friend class KFCurve;
	KFBX_FCURVE_INLINE KFCurveKey(const KPriFCurveKey& pKey, const KPriFCurveKeyAttr& pAttr);
	KFBX_FCURVE_INLINE KPriFCurveKeyAttr GetKeyAttr() const;

private:
	KTime mTime;
	kFCurveDouble mValue;			
	kUInt32 mFlags;

	#ifdef KFCURVE_FLOAT
		float  mData[4];
	#else 
		double	mData[2];
		kInt16	mWeight[2];
		kInt16	mVelocity[2];
	#endif 	

	#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS

};

#ifdef KFCURVE_FLOAT
extern void TangentWeightAndAdjustTangent(EKFCurveDataIndex pIndex, kFCurveDouble pWeight, float mData[4]);
#else
extern void TangentWeightAndAdjustTangent(EKFCurveDataIndex pIndex, kFCurveDouble pWeight, double mData[2], kInt16 mWeight[2]);
#endif

const int KEY_BLOCK_SIZE	= 1024;
const int KEY_BLOCK_COUNT	= KEY_BLOCK_SIZE/sizeof (KPriFCurveKey);

const int KEY_LIST_BLOCK_SIZE	= 256;
const int KEY_LIST_BLOCK_COUNT	= KEY_LIST_BLOCK_SIZE/sizeof (KPriFCurveKey *);


/** Function curve class. 
* A function curve is basically a collection of keys (see class KFCurveKey) 
* sorted in time order. Since it is a function, only one key per time is
* allowed. 
* \nosubgrouping
*/
class KFBX_DLL KFCurve
{

public:

    /**
    * \name Constructor and Destructor
    */
    //@{

    //! Constructor.
    KFCurve();

    //! Destructor.
    virtual ~KFCurve();

    void Destroy(int Local=0);

    //@}

    /**	Get function curve color.
    *	\return Pointer to an array of 3 elements: RGB values on a scale from 0 to 1.
    */
    float* GetColor();

    /** Set function curve color.
    *	\param pColor Pointer to an array of 3 elements: RGB values on a scale from 0 to 1.
    */
    void SetColor(const float *pColor);

    /** Set default value.
    * Default value is used when there is no key in the function curve.
    *	\param pValue Default value.
    */
    void SetValue(kFCurveDouble pValue);

    /** Get default value.
    * Default value is used when there is no key in the function curve.
    *	\return Default value.
    */
    KFBX_FCURVE_INLINE kFCurveDouble GetValue() const;

    /**
    * \name Key Management
    */
    //@{

    /** Resize fcurve buffer to hold a certain number of key.
    * \param pKeyCount Number of key the function curve will eventually hold.
  * \param pResetKeyCount If true, key count will be reset to 0
    */
    void ResizeKeyBuffer(int pKeyCount, bool pResetKeyCount = false);

    /** Call this function prior to modifying the keys of a function curve.
    * Call function KFCurve::KeyModifyEnd() after modification of the keys
    * are completed.
    */
    void KeyModifyBegin ();

    /** Call this function after modification of the keys of a function curve.
    * Call function KFCurve::KeyModifyBegin() prior to modifying the keys.
    */
    void KeyModifyEnd ();

    //! Get the number of keys.
    int KeyGetCount () const;

    //! Get the number of selected keys.
    int KeyGetSelectionCount () const;

    //! Select all keys.
    void KeySelectAll ();

    //! Deselect all keys.
    void KeyUnselectAll ();

    /** Get key at given index.
    * \param pIndex The index.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    KFCurveKey KeyGet(kFCurveIndex pIndex) const;

    //! Remove all the keys and free buffer memory.
    void KeyClear ();

    //! Minimize use of buffer memory.
    void KeyShrink();

    /** Set key at given index.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * \param pIndex Index of where the key should be set
    * \param pKey the key to set
    * \return true if key time is superior to previous key 
    * and inferior to next key.
    */
    bool	KeySet(kFCurveIndex pIndex, KFCurveKey& pKey);

    /** Set key at given index.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * \param pIndex Index of where the key should be set
    * \param pSourceCurve The source curve whose key at pSourceIndex is copied.
    * \param pSourceIndex The source key index.
    * \return true if key time is superior to previous key 
    * and inferior to next key.
    */
    bool	KeySet(kFCurveIndex pIndex, KFCurve* pSourceCurve, int pSourceIndex);

    /** Change time of key found at given index.
    *	\param pIndex Index of key to move.
    *	\param pTime Destination time.
    *	\return New index of moved key.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    int KeyMove(kFCurveIndex pIndex, KTime pTime);

    /** Add time and value offsets to keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pDeltaTime Time offset added to keys.
    *	\param pDeltaValue Value offset added to keys.
    *	\return true on success.
    */
    bool KeyMoveOf (bool pSelectedOnly, KTime pDeltaTime, kFCurveDouble pDeltaValue);

    /** Set value of keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pValue Value set to keys.
    *	\return true on success.
    */
    bool KeyMoveValueTo (bool pSelectedOnly, kFCurveDouble pValue);

    /** Scale value of keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key values.
    *	\return true on success.
    */
    bool KeyScaleValue (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Scale tangent of keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key tangents.
    *	\return true on success.
    */
    bool KeyScaleTangeant (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Scale value and tangent of keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pMultValue Scale applied on key values and tangents.
    *	\return true on success.
    */
    bool KeyScaleValueAndTangeant (bool pSelectedOnly, kFCurveDouble pMultValue);

    /** Remove key at given index.
    *	\param pIndex Index of key to remove.
    *	\return true on success.
    */
    bool KeyRemove(kFCurveIndex pIndex);

    /** Insert a key at given time.
    *	This function SHOULD be used instead of KFCurve::KeyAdd() if the key 
    * is to be added in the curve and not at the end. It inserts the key in 
    * respect to the interpolation type and tangents of the neighboring keys. 
    * If there is already a key a the given time, the key is modified and no 
    * new key is added.
    *	\param pTime Time to insert the key.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was inserted 
    * or already present.
    * \remarks Key value must be set explicitly afterwards. The 
    * interpolation type and tangent mode are copied from the previous key.
    */
    int KeyInsert ( KTime pTime, kFCurveIndex* pLast = NULL );

    /** Add a key at given time.
    *	Function KFCurve::KeyInsert() SHOULD be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect the interpolation type and tangents of the neighboring keys. 
    * If there is already a key at the given time, the key is modified and no 
    * new key is added.
    *	\param pTime Time to add the key.
    * \param pKey Key to add.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was added 
    * or already present.
    * \remarks Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */
    int KeyAdd (KTime pTime, KFCurveKey& pKey, kFCurveIndex* pLast = NULL);

    /** Add a key at given time.
    *	Function KFCurve::KeyInsert() SHOULD be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect the interpolation type and tangents of the neighboring keys. 
    * If there is already a key at the given time, the key is modified and no 
    * new key is added.
    * \param pTime Time to add the key.
    * \param pSourceCurve The source curve whose key at pSourceIndex is added.
    * \param pSourceIndex The source key index.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    * \return Index of the key at given time, no matter if it was added 
    * or already present.
    * \remarks Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */ 
    int KeyAdd(KTime pTime, KFCurve* pSourceCurve, int pSourceIndex, kFCurveIndex* pLast = NULL);

    /** Add a key at given time.
    *	Function KFCurve::KeyInsert() SHOULD be used instead if the key 
    * is to be added in the curve and not at the end. This function does not
    * respect of the interpolation type and tangents of the neighboring keys. 
    * If there is already a key a the given time, no key is added.
    *	\param pTime Time to add the key.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Index of the key at given time, no matter if it was added 
    * or already present.
    * \remarks Key value, interpolation type and tangent mode must be set 
    * explicitly afterwards.
    */
    int KeyAdd (KTime pTime, kFCurveIndex* pLast = NULL);

    /** Append a key at the end of the function curve.
    * \param pAtTime Time of appended key, must be superior to the 
    * last key time.
    * \param pSourceCurve Source curve.
    * \param pSourceIndex Index of the source key in the source curve.
    * \return Index of appended key or -1 if pAtTime is inferior to the last key's time.
    */
    int KeyAppend(KTime pAtTime, KFCurve* pSourceCurve, int pSourceIndex);

    /** Append a key at the end of the function curve.
    * \param pTime Time of appended key, must be superior to the 
    * last key time.
    * \param pValue Value of appended key.
    * \return Index of appended key or -1 if pTime is inferior to the last key's time.
    * \remarks Interpolation type of the appended key is set to 
    * KFCURVE_INTERPOLATION_CUBIC and tangent mode is set to 
    * KFCURVE_TANGEANT_AUTO.
    */
    int KeyAppendFast( KTime pTime, kFCurveDouble pValue );

    /** Find key index for a given time.
    *	\param pTime Time of the key looked for.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Key index. The integer part of the key index gives the 
    * index of the closest key with a smaller time. The decimals give
    * the relative position of given time compared to previous and next
    * key times. Returns -1 if function curve has no key.
    */
    double KeyFind (KTime pTime, kFCurveIndex* pLast = NULL);	

    //@}

    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/


    /**
    * \name Key Manipulation
    */
    //@{

    /** Set a key.
    *	Use SetTCB() to set a key with cubic interpolation and TCB tangent type.
    *   \param pKeyIndex        Key index
    *	\param pTime			Key time.
    *	\param pValue			Key value.
    *	\param pInterpolation	Key interpolation type.	Interpolation types are: 
    *							KFCURVE_INTERPOLATION_CONSTANT, 
    *							KFCURVE_INTERPOLATION_LINEAR,
    *							KFCURVE_INTERPOLATION_CUBIC
    *	\param pTangentMode		Key tangent mode (meaningful for cubic 
    *							interpolation only). Tangent modes are: 
    *							KFCURVE_TANGEANT_AUTO,
    *							KFCURVE_TANGEANT_USER,
    *							KFCURVE_TANGEANT_BREAK
    *	\param pRightSlope			Right slope.
    *	\param pNextLeftSlope		Next left slope.
    *	\param pTangentWeightMode	Weight mode if used
    *								KFCURVE_WEIGHTED_NONE
    *								KFCURVE_WEIGHTED_RIGHT
    *								KFCURVE_WEIGHTED_NEXT_LEFT
    *								KFCURVE_WEIGHTED_ALL
    *	\param pWeight0				Right slope weight.
    *	\param pWeight1				Next left slope weight.
    *	\param pVelocity0			Right velocity.
    *	\param pVelocity1			Next left velocity.
    */
    KFBX_FCURVE_INLINE void KeySet 
        (
        kFCurveIndex pKeyIndex,
        KTime pTime, 
        kFCurveDouble pValue, 
        kFCurveInterpolation pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
        kFCurveTangeantMode pTangentMode = KFCURVE_TANGEANT_AUTO, 
        kFCurveDouble pRightSlope = 0.0,
        kFCurveDouble pNextLeftSlope = 0.0,
        kFCurveTangeantWeightMode pTangentWeightMode = KFCURVE_WEIGHTED_NONE, 
        kFCurveDouble pWeight0                             = KFCURVE_DEFAULT_WEIGHT,
        kFCurveDouble pWeight1                             = KFCURVE_DEFAULT_WEIGHT,
        kFCurveDouble pVelocity0 = KFCURVE_DEFAULT_VELOCITY,
        kFCurveDouble pVelocity1 = KFCURVE_DEFAULT_VELOCITY
        );

    /**	Set a key with cubic interpolation, TCB tangent mode.
    *   \param pKeyIndex  Key index
    *	\param pTime	Key time.
    *	\param pValue	Key value.
    *	\param pData0	Tension.
    *	\param pData1	Continuity.
    *	\param pData2	Bias.
    */
    KFBX_FCURVE_INLINE void KeySetTCB 
        (
        kFCurveIndex pKeyIndex,
        KTime pTime, 
        kFCurveDouble pValue, 
        float pData0 = 0.0f, 
        float pData1 = 0.0f, 
        float pData2 = 0.0f
        );

    /** Get key interpolation type.
    *	Interpolation types are: KFCURVE_INTERPOLATION_CONSTANT, 
    *							 KFCURVE_INTERPOLATION_LINEAR,
    *							 KFCURVE_INTERPOLATION_CUBIC
    *   \param pKeyIndex         Key index
    *   \return                  Key interpolation type
    */
    KFBX_FCURVE_INLINE kFCurveInterpolation KeyGetInterpolation(kFCurveIndex pKeyIndex) const;

    /** Set key interpolation type.
    *   \param pKeyIndex      Key index
    *	\param pInterpolation Key interpolation type.
    *	Interpolation types are: KFCURVE_INTERPOLATION_CONSTANT, 
    *							 KFCURVE_INTERPOLATION_LINEAR,
    *							 KFCURVE_INTERPOLATION_CUBIC
    */
    KFBX_FCURVE_INLINE void KeySetInterpolation(kFCurveIndex pKeyIndex, kFCurveInterpolation pInterpolation);

    /** Get key constant mode.
    *	Warning: This method is meaningful for constant interpolation only.
    *			 Using this method for non constant interpolated key will return unpredicted value.
    * Constant modes are:		KFCURVE_CONSTANT_STANDARD
    *							KFCURVE_CONSTANT_NEXT
    *   \param pKeyIndex      Key index
    *	\return Key constant mode.
    */
    KFBX_FCURVE_INLINE kFCurveConstantMode KeyGetConstantMode(kFCurveIndex pKeyIndex) const;

    /** Get key tangent mode.
    *   \param pKeyIndex  
    *   \param pIncludeOverrides
    *	Warning: This method is meaningful for cubic interpolation only.
    *			 Using this method for non cubic interpolated key will return unpredicted value.
    *	Tangent modes are: KFCURVE_TANGEANT_AUTO,
    *					   KFCURVE_TANGEANT_AUTO_BREAK
    *					   KFCURVE_TANGEANT_TCB,
    *					   KFCURVE_TANGEANT_USER,
    *					   KFCURVE_TANGEANT_BREAK
    *	\return Key tangent mode.
    */
    KFBX_FCURVE_INLINE kFCurveTangeantMode KeyGetTangeantMode(kFCurveIndex pKeyIndex, bool pIncludeOverrides = false ) const;

    /** Get key tangent weight mode.
    *	Warning: This method is meaningful for cubic interpolation only.
    *	Tangent weight modes are:	KFCURVE_WEIGHTED_NONE,
    *								KFCURVE_WEIGHTED_RIGHT,
    *								KFCURVE_WEIGHTED_NEXT_LEFT,
    *								KFCURVE_WEIGHTED_ALL
    * \param pKeyIndex The key index.
    */
    KFBX_FCURVE_INLINE kFCurveTangeantWeightMode KeyGetTangeantWeightMode(kFCurveIndex pKeyIndex) const;

    /** Get key tangent velocity mode.
    *	Warning: This method is meaningful for cubic interpolation only.
    *	Tangent weight modes are:	KFCURVE_VELOCITY_NONE,
    *								KFCURVE_VELOCITY_RIGHT,
    *								KFCURVE_VELOCITY_NEXT_LEFT,
    *								KFCURVE_VELOCITY_ALL
    * \param pKeyIndex The key index.
    */
    KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode KeyGetTangeantVelocityMode(kFCurveIndex pKeyIndex) const;

    /** Set key constant mode.
    *	Warning: This method is meaningful for constant interpolation only.
    *   \param pKeyIndex            Key index
    *	\param pMode Key constant mode.
    *	Constant modes are:		KFCURVE_CONSTANT_STANDARD
    *							KFCURVE_CONSTANT_NEXT
    */
    KFBX_FCURVE_INLINE void KeySetConstantMode(kFCurveIndex pKeyIndex, kFCurveConstantMode pMode);

    /** Set key tangent mode.
    *	Warning: This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Key index
    *	\param pTangent Key tangent mode.
    *	Tangent modes are: KFCURVE_TANGEANT_AUTO,
    *					   KFCURVE_TANGEANT_AUTO_BREAK
    *					   KFCURVE_TANGEANT_TCB,
    *					   KFCURVE_TANGEANT_USER,
    * 				   KFCURVE_TANGEANT_BREAK
  * \param pIgnoreAutoTimeIndepedentConversion \b true ignore the auto time independent conversion flag.
    */
	KFBX_FCURVE_INLINE void KeySetTangeantMode(kFCurveIndex pKeyIndex, kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion = false);

    /** Set key tangent weight mode as double value (cubic interpolation, non TCB tangent mode).
    *	Warning: This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Key index
    *	\param pTangentWeightMode	Weight mode
    *								KFCURVE_WEIGHTED_NONE
    *								KFCURVE_WEIGHTED_RIGHT
    *								KFCURVE_WEIGHTED_NEXT_LEFT
    *								KFCURVE_WEIGHTED_ALL
    *	\param pMask				Used to select the affected tangents
    *								KFCURVE_WEIGHTED_RIGHT
    *								KFCURVE_WEIGHTED_NEXT_LEFT
    *								KFCURVE_WEIGHTED_ALL
    */

    KFBX_FCURVE_INLINE void KeySetTangeantWeightMode(kFCurveIndex pKeyIndex, kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask = KFCURVE_WEIGHTED_ALL );

    /** Set key tangent velocity mode as double value (cubic interpolation, non TCB tangent mode).
    *	Warning: This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Key index
    *	\param pTangentVelocityMode	Weight mode
    *								KFCURVE_VELOCITY_NONE
    *								KFCURVE_VELOCITY_RIGHT
    *								KFCURVE_VELOCITY_NEXT_LEFT
    *								KFCURVE_VELOCITY_ALL
    *	\param pMask				Used to select the affected tangents
    *								KFCURVE_VELOCITY_RIGHT
    *								KFCURVE_VELOCITY_NEXT_LEFT
    *								KFCURVE_VELOCITY_ALL
    */

    KFBX_FCURVE_INLINE void KeySetTangeantVelocityMode(kFCurveIndex pKeyIndex, kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask = KFCURVE_VELOCITY_ALL );


    /** Get key data as double value (cubic interpolation, non TCB tangent mode).
    *	Warning: Using this method for other than cubic interpolated 
    *			 key (linear, constant) will return unpredicted values.
    *	Warning: Slope data is inconsistent for automatic tangent mode.
    *			 Use KFCurve::EvaluateLeftDerivative() and 
    *			 KFCurve::EvaluateRightDerivative() to find
    *			 slope values.
    *	Warning: Using this method for TCB tangent mode key will return 
    *			 unpredicted values. Use KFCurve::GetDataFloat() instead.
    *   \param pKeyIndex   Key index
    *	\param pIndex Data index, either	KFCURVEKEY_RIGHT_SLOPE,
    *										KFCURVEKEY_NEXT_LEFT_SLOPE.
    *										KFCURVEKEY_NEXT_RIGHT_WEIGHT.
    *										KFCURVEKEY_NEXT_LEFT_WEIGHT
    */
    KFBX_FCURVE_INLINE kFCurveDouble KeyGetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const;

    /**	Set data as double value (cubic interpolation, non TCB tangent mode).
    *	Warning: Using this method for other than cubic interpolated 
    *			 key (linear, constant) is irrelevant.
    *	Warning: Slope data is inconsistent for automatic tangent mode.
    *			 Therefore, it is irrelevant to use this method on automatic 
    *			 tangent mode keys.
    *	Warning: Using this method for a TCB tangent mode key will result
    *			 in unpredicted curve behavior for this key. Use KFCurve::SetDataFloat() 
    *			 instead.
    *   \param pKeyIndex   Key index
    *	\param pIndex Data index, either	KFCURVEKEY_RIGHT_SLOPE,
    *										KFCURVEKEY_NEXT_LEFT_SLOPE.
    *										KFCURVEKEY_NEXT_RIGHT_WEIGHT.
    *										KFCURVEKEY_NEXT_LEFT_WEIGHT
    *	\param pValue	The data value to set (a slope or a weight).
    */
    KFBX_FCURVE_INLINE void KeySetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, kFCurveDouble pValue);

    /** Get key data as float value (cubic interpolation, TCB tangent mode).
    *	Warning: Using this method for any key but a cubic interpolated,
    *			 in TCB tangent mode, will return unpredicted values.
    *   \param pKeyIndex   Key index
    *	\param pIndex	Data index, either KFCURVEKEY_TCB_TENSION, KFCURVEKEY_TCB_CONTINUITY or KFCURVEKEY_TCB_BIAS.
    */	
    KFBX_FCURVE_INLINE float KeyGetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const;

    /**	Set data as float value (cubic interpolation, TCB tangent mode).
    *	Warning: Using this method for any key but a cubic interpolated,
    *			 in TCB tangent mode, will return unpredicted values.
    *   \param pKeyIndex   Key index
    *	\param pIndex	Data index, either KFCURVEKEY_TCB_TENSION, KFCURVEKEY_TCB_CONTINUITY or KFCURVEKEY_TCB_BIAS.
    *	\param pValue	The data value to set.
    */
    KFBX_FCURVE_INLINE void KeySetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, float pValue);

    /**	Get key data as a pointer
    *	Warning: not supported in 'double' mode.
    * \param pKeyIndex Key index.
    */
    KFBX_FCURVE_INLINE const float* KeyGetDataPtr(kFCurveIndex pKeyIndex) const;

    /**	Get key value.
    * \param pKeyIndex Key index.
    */
    KFBX_FCURVE_INLINE kFCurveDouble KeyGetValue(kFCurveIndex pKeyIndex) const;

    /** Set key value.
    * \param pKeyIndex Key index.
    * \param pValue The value to set.
    */ 
    KFBX_FCURVE_INLINE void KeySetValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Increment key value.
    *   \param pKeyIndex   Key index
    *	\param pValue Value by which key value is incremented.
    */
    KFBX_FCURVE_INLINE void KeyIncValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Multiply key value.
    *   \param pKeyIndex   Key index
    *	\param pValue Value by which the key value is multiplied.
    */
    KFBX_FCURVE_INLINE void KeyMultValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Multiply key tangents.
    *	Note: When multiplying a key value, tangents must be
    *         multiplied to conserve the same topology.
    *   \param pKeyIndex   Key index
    *	\param pValue Value by which key tangents are multiplied.
    */
    KFBX_FCURVE_INLINE void KeyMultTangeant(kFCurveIndex pKeyIndex, kFCurveDouble pValue);

    /** Get key time
    *   \param pKeyIndex   Key index
    *	\return Key time (time at which this key is occurring).
    */
    KFBX_FCURVE_INLINE KTime KeyGetTime(kFCurveIndex pKeyIndex) const;

    /** Set key time.
    *   \param pKeyIndex   Key index
    *	\param pTime Key time (time at which this key is occurring).
    */
    KFBX_FCURVE_INLINE void KeySetTime(kFCurveIndex pKeyIndex, KTime pTime);

    /** Increment key time.
    *   \param pKeyIndex   Key index
    *	\param pTime Time value by which the key time is incremented.
    */
    KFBX_FCURVE_INLINE void KeyIncTime(kFCurveIndex pKeyIndex, KTime pTime);

    /** Set if key is currently selected.
    *   \param pKeyIndex   Key index
    *	\param pSelected Selection flag.
    */
    KFBX_FCURVE_INLINE void KeySetSelected(kFCurveIndex pKeyIndex, bool pSelected);	

    /** Return if key is currently selected.
    *   \param pKeyIndex   Key index
    *	\return Selection flag.
    */
    KFBX_FCURVE_INLINE bool KeyGetSelected(kFCurveIndex pKeyIndex) const;

    /** Set if key is currently marked for manipulation.
    *   \param pKeyIndex   Key index
    *	\param pMark Mark flag.
    */
    KFBX_FCURVE_INLINE void KeySetMarkedForManipulation(kFCurveIndex pKeyIndex, bool pMark);	

    /** Return if key is currently marked for manipulation.
    *   \param pKeyIndex   Key index
    *	\return Mark flag.
    */
    KFBX_FCURVE_INLINE bool KeyGetMarkedForManipulation(kFCurveIndex pKeyIndex) const;

    /** Set tangent visibility mode.
    *	Warning: This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Key index
    *	\param pVisibility	Tangent visibility mode.
    *	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
    *						          KFCURVE_TANGEANT_SHOW_LEFT
    *						          KFCURVE_TANGEANT_SHOW_RIGHT
    */
    KFBX_FCURVE_INLINE void	KeySetTangeantVisibility (kFCurveIndex pKeyIndex, kFCurveTangeantVisibility pVisibility);	

    /** Return tangent visibility mode.
    *	Warning: This method is meaningful for cubic interpolation only.
    *   \param pKeyIndex   Key index
    *	\return Tangent visibility mode.
    *	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
    *			                      KFCURVE_TANGEANT_SHOW_LEFT
    *			                      KFCURVE_TANGEANT_SHOW_RIGHT
    */
    KFBX_FCURVE_INLINE kFCurveTangeantVisibility KeyGetTangeantVisibility (kFCurveIndex pKeyIndex) const;

    /** Set/Unset Break tangent
    * Only valid for User and Auto keys
    * \param pKeyIndex Key index.
    * \param pVal Break flag.
    */
    KFBX_FCURVE_INLINE void KeySetBreak(kFCurveIndex pKeyIndex, bool pVal); 

    /** Get if tangent is break
    * Only valid for User and Auto keys
    * \param pKeyIndex Key index.
    */
    KFBX_FCURVE_INLINE bool KeyGetBreak(kFCurveIndex pKeyIndex) const; 

    //@}

    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/
    /************************************************************************************************/

    /**
    * \name Key Tangent Management
    */
    //@{

    /** Set interpolation type on keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pInterpolation Interpolation type.
    */
    void KeyTangeantSetInterpolation(bool pSelectedOnly, kFCurveInterpolation pInterpolation);

    /** Set tangent mode on keys, all or selected only.
    *	\param pSelectedOnly If set to \c true, only selected keys are affected.
    * Otherwise, all keys are affected.
    *	\param pTangentMode Tangent mode.
    * \remarks Tangent mode is only relevant on keys with a cubic interpolation type.
    */
    void KeyTangeantSetMode(bool pSelectedOnly, kFCurveTangeantMode pTangentMode);

    /** Get the left derivative of a key.
    *	\param pIndex Index of key.
    *	\return Left derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetLeftDerivative(kFCurveIndex pIndex);

    /** Set the left derivative of a key.
    *	\param pIndex Index of key.
    *	\param pValue Left derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO. 
    */
    void KeySetLeftDerivative(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** Get the left auto parametric of a key.
    *	\param pIndex Index of key.
    *	\param pApplyOvershootProtection Clamp is taking into account.
    *	\return left auto parametric.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetLeftAuto(kFCurveIndex pIndex, bool pApplyOvershootProtection = false);

    /** Set the left auto parametric  of a key.
    *	\param pIndex Index of key.
    *	\param pValue Left auto parametric .
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetLeftAuto(kFCurveIndex pIndex, kFCurveDouble pValue);	

    /** Get the left derivative info of a key.
    *	\param pIndex Index of key.
    *	\return Left derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    KFCurveTangeantInfo KeyGetLeftDerivativeInfo(kFCurveIndex pIndex);

    /** Set the left derivative info of a key.
    *	\param pIndex Index of key.
    *	\param pValue Left derivative.
    *   \param pForceDerivative
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */

    void KeySetLeftDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false);


    /** Increment the left derivative of a key.
    *	\param pIndex Index of key.
    *	\param pInc Increment to left derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyIncLeftDerivative(kFCurveIndex pIndex, kFCurveDouble pInc);

    /** Get the right derivative of a key.
    *	\param pIndex Index of key.
    *	\return Right derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetRightDerivative(kFCurveIndex pIndex);

    /** Set the right derivative of a key.
    *	\param pIndex Index of key.
    *	\param pValue Right derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetRightDerivative(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** Get the right auto parametric of a key.
    *	\param pIndex Index of key.
    *	\param pApplyOvershootProtection Clamp is taking into account.
    *	\return Right auto parametric.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    kFCurveDouble KeyGetRightAuto(kFCurveIndex pIndex, bool pApplyOvershootProtection = false);

    /** Set the right auto parametric  of a key.
    *	\param pIndex Index of key.
    *	\param pValue Right auto parametric .
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER, KFCURVE_TANGEANT_BREAK or KFCURVE_TANGEANT_AUTO.
    */
    void KeySetRightAuto(kFCurveIndex pIndex, kFCurveDouble pValue);


    /** Get the right derivative info of a key.
    *	\param pIndex Index of key.
    *	\return Right derivative info.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    KFCurveTangeantInfo KeyGetRightDerivativeInfo(kFCurveIndex pIndex);

    /** Set the right derivative info of a key.
    *	\param pIndex Index of key.
    *	\param pValue Right derivative.
    *   \param pForceDerivative
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetRightDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false);


    /** Increment the right derivative of a key.
    *	\param pIndex Index of key.
    *	\param pInc Increment to right derivative.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyIncRightDerivative(kFCurveIndex pIndex, kFCurveDouble pInc);

    /** This function is disabled and always return 0.
    * \param pIndex Key index.
    */
    kFCurveDouble KeyGetRightBezierTangeant(kFCurveIndex pIndex);

    /** Set the left derivative of a key as a Bezier tangent.
    *	\param pIndex Index of key.
    *	\param pValue Left derivative as a Bezier tangent.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetLeftBezierTangeant(kFCurveIndex pIndex, kFCurveDouble pValue);

    /** This function is disabled and always returns 0.
    * \param pIndex Key index.
    */
    kFCurveDouble KeyGetLeftBezierTangeant(kFCurveIndex pIndex);

    /** Set the right derivative of a key as a Bezier tangent.
    *	\param pIndex Index of key.
    *	\param pValue Right derivative as a Bezier tangent.
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeySetRightBezierTangeant(kFCurveIndex pIndex, kFCurveDouble pValue);


    /** Multiply the Derivative of a key.
    *	\param pIndex Index of key.
    *	\param pMultValue Value that multiply Derivative
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    * This function is only relevant if key interpolation is 
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void KeyMultDerivative(kFCurveIndex pIndex, kFCurveDouble pMultValue);

    /** Get the left tangent weight mode of a key
    *	\param pIndex Index of key.
    *	\return true if the key is weighted
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    bool KeyIsLeftTangeantWeighted(kFCurveIndex pIndex) const;

    /** Get the right tangent weight mode of a key
    *	\param pIndex Index of key.
    *	\return true if the key is weighted
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    bool KeyIsRightTangeantWeighted(kFCurveIndex pIndex) const;

    /** Set the left tangent weight mode of a key
    *	\param pIndex Index of key.
    *	\param pWeighted Weighted state of the tangent
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetLeftTangeantWeightedMode( kFCurveIndex pIndex, bool pWeighted);

    /** Set the right tangent weight mode of a key
    *	\param pIndex Index of key.
    *	\param pWeighted Weighted state of the tangent
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetRightTangeantWeightedMode( kFCurveIndex pIndex, bool pWeighted);

    /** Get the weight value component of the left tangent of a key
    *	\param pIndex Index of key.
    *	\return right tangent weight
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */
    kFCurveDouble KeyGetLeftTangeantWeight(kFCurveIndex pIndex) const;

    /** Get the weight value component of the right tangent of a key
    *	\param pIndex Index of key.
    *	\return right tangent weight
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */		
    kFCurveDouble KeyGetRightTangeantWeight(kFCurveIndex pIndex) const;

    /** Set the left tangent weight of a key
    *	\param pIndex Index of key.
    *	\param pWeight Weight
    *   \param pAdjustTan If true, recompute the tangent height to compensate for very small weights
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in weighted mode.
    *
    * The pAdjustTan option will only produce correct results provided that the tangent has already been
    * set before calling this function.
    */
    void   KeySetLeftTangeantWeight( kFCurveIndex pIndex, kFCurveDouble pWeight, bool pAdjustTan = false );

    /** Set the right tangent weight of a key
    *	\param pIndex Index of key.
    *	\param pWeight Weight
    *   \param pAdjustTan If true, recompute the tangent height to compensate for very small weights
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in weighted mode.
    *
    * The pAdjustTan option will only produce correct results provided that the tangent has already been
    * set before calling this function.
    */
    void   KeySetRightTangeantWeight( kFCurveIndex pIndex, kFCurveDouble pWeight, bool pAdjustTan = false  );

    /** Get the left tangent velocity mode of a key
    *	\param pIndex Index of key.
    *	\return true if the key has velocity
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    bool KeyIsLeftTangeantVelocity(kFCurveIndex pIndex) const;

    /** Get the right tangent velocity mode of a key
    *	\param pIndex Index of key.
    *	\return true if the key has velocity
    * \remarks Result is undetermined if function curve has no key or index 
    * is out of bounds.
    */
    bool KeyIsRightTangeantVelocity(kFCurveIndex pIndex) const;

    /** Set the left tangent velocity mode of a key
    *	\param pIndex Index of key.
    *	\param pVelocity Velocity state of the tangent
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetLeftTangeantVelocityMode( kFCurveIndex pIndex, bool pVelocity );

    /** Set the right tangent velocity mode of a key
    *	\param pIndex Index of key.
    *	\param pVelocity Velocity state of the tangent
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK.
    */
    void   KeySetRightTangeantVelocityMode( kFCurveIndex pIndex, bool pVelocity);

    /** Get the velocity value component of the left tangent of a key
    *	\param pIndex Index of key.
    *	\return right tangent velocity
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */
    kFCurveDouble KeyGetLeftTangeantVelocity(kFCurveIndex pIndex) const;

    /** Get the velocity value component of the right tangent of a key
    *	\param pIndex Index of key.
    *	\return right tangent velocity
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC
    */		
    kFCurveDouble KeyGetRightTangeantVelocity(kFCurveIndex pIndex) const;

    /** Set the left tangent velocity of a key
    *	\param pIndex Index of key.
    *	\param pVelocity Velocity
    * This function is only relevant if previous key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in velocity mode.
    */
    void   KeySetLeftTangeantVelocity( kFCurveIndex pIndex, kFCurveDouble pVelocity );

    /** Set the right tangent velocity of a key
    *	\param pIndex Index of key.
    *	\param pVelocity Velocity
    * This function is only relevant if key interpolation
    * type is KFCURVE_INTERPOLATION_CUBIC and tangent mode is
    * KFCURVE_TANGEANT_USER or KFCURVE_TANGEANT_BREAK. The tangent is 
    * automatically set in velocity mode.
    */
    void   KeySetRightTangeantVelocity( kFCurveIndex pIndex, kFCurveDouble pVelocity );

    //@}

    /**
    * \name Extrapolation 
    * Extrapolation defines the function curve value before and after the keys.
    * Pre-extrapolation defines the function curve value before first key.
    * Post-extrapolation defines the function curve value after last key.
    * <ul><li>KFCURVE_EXTRAPOLATION_CONST means a constant value matching the first/last key
    *	    <li>KFCURVE_EXTRAPOLATION_REPETITION means the entire function curve is looped
    *		<li>KFCURVE_EXTRAPOLATION_MIRROR_REPETITION means the entire function curve is looped once backward, once forward and so on 
    *		<li>KFCURVE_EXTRAPOLATION_KEEP_SLOPE means a linear function with a slope matching the first/last key</ul>
    */
    //@{

    /** Set pre-extrapolation mode.
    * \param pExtrapolation The pre-extrapolation mode to set.
    */
    KFBX_FCURVE_INLINE void SetPreExtrapolation(kFCurveExtrapolationMode pExtrapolation);

    //! Get pre-extrapolation mode.
    KFBX_FCURVE_INLINE kFCurveExtrapolationMode GetPreExtrapolation() const;

    /** Set pre-extrapolation count.
    *	\param pCount Number of repetitions if pre-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION.
    */
    KFBX_FCURVE_INLINE void SetPreExtrapolationCount(kULong pCount);

    /** Get pre-extrapolation count.
    *	\return Number of repetitions if pre-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION.
    */
    KFBX_FCURVE_INLINE kULong GetPreExtrapolationCount() const;

    /** Set post-extrapolation mode.
    * \param pExtrapolation The post-extrapolation mode to set.
    */
    KFBX_FCURVE_INLINE void SetPostExtrapolation(kFCurveExtrapolationMode pExtrapolation);

    //! Get post-extrapolation mode.
    KFBX_FCURVE_INLINE kFCurveExtrapolationMode GetPostExtrapolation() const;

    /** Set post-extrapolation count.
    *	\param pCount Number of repetitions if post-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION.
    */
    KFBX_FCURVE_INLINE void SetPostExtrapolationCount(kULong pCount);

    /** Get post-extrapolation count.
    *	\return Number of repetitions if post-extrapolation mode is
    * KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION.
    */
    KFBX_FCURVE_INLINE kULong GetPostExtrapolationCount() const;

    /** Get total number of keys taking extrapolation into account.
    * The total number of keys includes repetitions of the function 
    * curve if pre-extrapolation and/or post-extrapolation are of
    * mode KFCURVE_EXTRAPOLATION_REPETITION or KFCURVE_EXTRAPOLATION_MIRROR_REPETITION.
    *	\return Total number of keys taking extrapolation into account.
    */
    int KeyGetCountAll() const;

    /** Find key index for a given time taking extrapolation into account.
    *	\param pTime Time of the key looked for.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Key index between 0 and KFCurve::KeyGetCount() - 1.The 
    * integer part of the key index gives the index of the closest key 
    * with a smaller time. The decimals give the relative position of 
    * given time compared to previous and next key times. Return -1 if 
    * function curve has no key.
    */
    double KeyFindAll(KTime pTime, kFCurveIndex* pLast = NULL);

    //@}

    /**
    * \name Evaluation and Analysis
    */
    //@{

    /**	Evaluate function curve value at a given time.
    *	\param pTime Time of evaluation.
    * If time falls between two keys, function curve value is 
    * interpolated according to previous key interpolation type and
    * tangent mode if relevant.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Function curve value or default value if function curve
    * has no key.
    * \remarks This function takes extrapolation into account.
    */
    kFCurveDouble Evaluate (KTime pTime, kFCurveIndex* pLast = NULL);

    /**	Evaluate function curve value at a given key index.
    *	\param pIndex Any value between 0 and KFCurve::KeyGetCount() - 1.
    * If key index is not an integer value, function curve value is 
    * interpolated according to previous key interpolation type and
    * tangent mode if relevant.
    *	\return Function curve value or default value if function curve
    * has no key.
    * \remarks This function does not take extrapolation into account.
    */
    kFCurveDouble EvaluateIndex( double pIndex);

    /**	Evaluate function left derivative at given time.
    *	\param pTime Time of evaluation.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Left derivative at given time.
    * \remarks This function does not take extrapolation into account.
    */
    kFCurveDouble EvaluateLeftDerivative (KTime pTime, kFCurveIndex* pLast = NULL);

    /**	Evaluate function right derivative at given time.
    *	\param pTime Time of evaluation.
    * \param pLast Function curve index to speed up search. If this 
    * function is called in a loop, initialize this value to 0 and let it 
    * be updated by each call.
    *	\return Right derivative at given time.
    * \remarks This function does not take extrapolation into account.
    */
    kFCurveDouble EvaluateRightDerivative (KTime pTime, kFCurveIndex* pLast = NULL);

    /**	Find the peaks time between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeakTime1 First peak time.
    *	\param pPeakTime2 Second peak time.
    *	\return Number of peaks found.
    * \remarks Result is undetermined if function curve has no key or 
    * index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, KTime& pPeakTime1, KTime& pPeakTime2);

    /**	Find the peaks value between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeak1 First peak value.
    *	\param pPeak2 Second peak value.
    *	\return Number of peaks found.
    * \remarks Result is undetermined if function curve has no key or 
    * index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, kFCurveDouble& pPeak1, kFCurveDouble& pPeak2);

    /**	Find the peaks time and value between 2 keys (a local minimum and/or maximum).
    *	\param pLeftKeyIndex Left key index (there must be a right key).
    *	\param pPeakTime1 First peak time.
    *	\param pPeak1 First peak value.
    *	\param pPeakTime2 Second peak time.
    *	\param pPeak2 Second peak value.
    *	\return Number of peaks found.
    * \remarks Result is undetermined if function curve has no key or 
    * index is out of bounds.
    */
    int FindPeaks(kFCurveIndex pLeftKeyIndex, KTime& pPeakTime1, kFCurveDouble& pPeak1, KTime& pPeakTime2, kFCurveDouble& pPeak2);

    /** Get key period statistics. If pAveragePeriod == pMinPeriod, we have iso-sampled data.
    *	\param pAveragePeriod Average key period.
    *	\param pMinPeriod Minimum period found.
    *	\param pMaxPeriod Maximum period found.
    */
    void KeyGetPeriods(KTime& pAveragePeriod, KTime& pMinPeriod, KTime& pMaxPeriod);

    //@}

    /**
    * \name Copy, Insert, Replace and Delete Functions
    */
    //@{

    /** Create a new function curve and copy keys.
    *	\param pStart Beginning of time range.
    *	\param pStop End of time range.
    *	\return Created function curve.
    *   \remarks All keys are always copied. To copy keys in a specific time range, use Replace().
    */
    HKFCurve Copy(KTime pStart = KTIME_MINUS_INFINITE, KTime pStop = KTIME_INFINITE);

    /** Copy a function curve content into current function curve.
    *	\param pSource Source function curve.
    *	\param pWithKeys If \c true, clear keys in current function curve and copy
    * keys from source function curve. If \c false, keys in current function curve
    * are left as is.
    */
    void CopyFrom(KFCurve& pSource, bool pWithKeys = true);

    /**	Replace keys within a range in current function curve with keys found in a source function curve.
    * \param pSource Source function curve.
    * \param	pStart Start of time range.
    * \param	pStop End of time range.
    * \param pUseExactGivenSpan false = original behavior where time of first and last key was used
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert.
    * \param pTimeSpanOffset
    */
    void Replace(HKFCurve pSource, KTime pStart = KTIME_MINUS_INFINITE, KTime pStop = KTIME_INFINITE, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, KTime pTimeSpanOffset = KTIME_ZERO );

    /**	Replace keys within a range in current function curve with keys found in a source function curve.
    * The copied keys have their value scaled with a factor varying 
    * linearly in time within the given time range.
    * \param pSource Source function curve.
    * \param pStart Start of time range.
    * \param pStop End of time range.
    * \param pScaleStart Scale factor applied at start of time range. 
    * \param pScaleStop Scale factor applied at end of time range. 
    * \param pUseExactGivenSpan false = original behavior where time of first and last key was used
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert.
    * \param pTimeSpanOffset
    */
    void ReplaceForQuaternion(HKFCurve pSource, KTime pStart, KTime pStop, kFCurveDouble pScaleStart, kFCurveDouble pScaleStop, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, KTime pTimeSpanOffset = KTIME_ZERO );

    /**	Replace keys within a range in current function curve with keys found in a source function curve.
    * \param pSource Source function curve.
    * \param pStart Start of time range.
    * \param pStop End of time range.
    * \param pAddFromStart Offset applied to copied key values within the time range.
    * \param pAddAfterStop Offset applied to key values after the time range.
    * \param pValueSubOffsetAfterStart If \c true, copied key values within 
	* the time range are subtracted from time offset specified by parameter
    * \c pAddFromStart. If \c false, copied key values within the time range are 
    * added to time offset specified by parameter \c pAddFromStart. 
    * \param pValueSubOffsetAfterStop If \c true, key values after 
	* the time range are subtracted from time offset specified by parameter
    * \c pAddAfterStop. If \c false, key values after the time range are 
    * added to time offset specified by parameter \c pAddAfterStop. 
    * \param pUseExactGivenSpan false = original behavior where time of first and last key was used
    * \param pKeyStartEndOnNoKey Inserts a key at the beginning and at the end of the range if there is no key to insert
    * \param pTimeSpanOffset
    */
    void ReplaceForEulerXYZ(HKFCurve pSource, KTime pStart, KTime pStop, kFCurveDouble pAddFromStart, kFCurveDouble pAddAfterStop, bool pValueSubOffsetAfterStart, bool pValueSubOffsetAfterStop, bool pUseExactGivenSpan = false, bool pKeyStartEndOnNoKey = true, KTime pTimeSpanOffset = KTIME_ZERO );	

    /**	Insert all keys found in a source function curve in current function curve.
    * A time offset is added to copied keys so that the first copied key occurs 
    * at the given insertion time. Keys from the source function curve are merged into 
    * the current function curve. In other words, no existing key in the current function
    * curve is destroyed unless there is an overlap with a copied key.
    * \param pSource Source function curve.
    * \param pInsertTime Insert time of the first key found in the source function curve.
    * \param pFirstKeyLeftDerivative First key left derivative.
    * \param pFirstKeyIsWeighted  First key left weighted state (true if weighted).
    * \param pFirstKeyWeight First key left weight
    */

    void Insert(HKFCurve pSource, KTime pInsertTime, kFCurveDouble pFirstKeyLeftDerivative, bool pFirstKeyIsWeighted = false, kFCurveDouble pFirstKeyWeight = KFCURVE_DEFAULT_WEIGHT);

    /**	Insert all keys found in a source function curve in current function curve.
    * A time offset is added to copied keys so that the first copied key occurs 
    * at the given insertion time. Keys from the source function curve are merged into 
    * the current function curve. In other words, no existing key in the current function
    * curve is destroyed unless there is an overlap with a copied key.
    * \param pSource Source function curve.
    * \param pInsertTime Insert time of the first key found in the source function curve.
    * \param pFirstKeyLeftDerivative First key left derivative info.
    */
    void Insert(HKFCurve pSource, KTime pInsertTime, KFCurveTangeantInfo pFirstKeyLeftDerivative );

    /** Delete keys within an index range.
    * Index range is inclusive.
    * This function is much faster than multiple removes.
    *	\param pStartIndex Index of first deleted key.
    *	\param pStopIndex Index of last deleted key.
    *	\return \c true if the function curve contains keys, \c false otherwise.
    * \remarks Result is undetermined if function curve has keys but an 
    * index is out of bounds.
    */
    bool Delete(kFCurveIndex pStartIndex , kFCurveIndex pStopIndex);									

    /** Delete keys within a time range.
    * This function is much faster than multiple removes.
    *	\param pStart Start of time range.
    *	\param pStop End of time range.
  * \param pInclusive Time range include the keys at pStart and pStop if true.
    *	\return \c true if the function curve contains keys, \c false otherwise.
    */	
	bool Delete (KTime pStart = KTIME_MINUS_INFINITE, KTime pStop = KTIME_INFINITE, bool pInclusive = false);

    /** Get if interpolation is cubic and that the tangents and weightings are untouched.
    *	\param	pKeyIndex	Index of the key to test.
    *	\return				Returns true if the interpolation is a pure cubic auto.
    */
    bool IsKeyInterpolationPureCubicAuto(kFCurveIndex pKeyIndex);

    /** Extract All Keys in the Given Selection Span
    *	\param	pArray	    Array where to Stored Found Keys.
    *	\param	pMinIndex	Index where to start the Search.
    *	\param	pMaxIndex	Index where to stop the Search (the last index is the limit, the Key at this index is not tested).
    *	\param	pMinValue	Minimal Value to Consider the Key.
    *	\param	pMaxValue	Maximal Value to Consider the Key.
    */
    void ExtractKeysIndex( KArrayTemplate<int> &pArray, int pMinIndex, int pMaxIndex, double pMinValue =  -K_DOUBLE_MAX, double pMaxValue =  K_DOUBLE_MAX);

    //@}

    ///////////////////////////////////////////////////////////////////////////////
    //
    //  WARNING!
    //
    //	Anything beyond these lines may not be documented accurately and is 
    // 	subject to change without notice.
    //
    ///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    typedef enum {
        V7 = 4007,
        V6 = 4005,
        V5 = 4004
    } FbxStoreVersionID;

    bool	FbxStore (KFbx* pFbx, bool pOnlyDefaults = false, bool pColor = true, FbxStoreVersionID pVersionID = V7 );
    bool	FbxRetrieve (KFbx* pFbx, bool pOnlyDefaults = false, bool pColor = false );
    bool	FbxInternalRetrieve (KFbx* pFbx, bool pOnlyDefaults = false, bool pColor = false );

	void	FbxStorePriKeyAndAttrArrays(KFbx* pFbx);
	void	FbxRetrievePriKeyAndAttrArrays(KFbx* pFbx);
    void	FbxRetrievePrePostExtrapolation(KFbx* pFbx);

    double CandidateEvaluate (KTime pTime, kFCurveIndex* pLast = NULL);
    bool CandidateClear ();
    bool CandidateSet (KTime pTime, double pValue);
    bool IsCandidate ();
    double CandidateGet ();
    KTime CandidateGetTime ();

    bool IsLocked() const;
    bool IsLockedByLayer() const;
    bool IsLockedByProperty() const;
    void SetLockedByLayer(bool pLocked);
    void SetLockedByProperty(bool pLocked);

    bool CandidateKey
        (
        kFCurveIndex	*pLast				= NULL, 
        int	pInterpolation = KFCURVE_INTERPOLATION_CUBIC, 
        int	pTanMode = KFCURVE_TANGEANT_USER, 
        int pContinuity = KFCURVE_CONTINUITY,
        bool			pTangeantOverride	= true,
        KTime			pCandidateTime		= KTIME_INFINITE,
        double			pKeyIndexTolerance  = 0.0
        );

    bool NormalsSeemsToComeFromAPlot();

    void SetWasData (int pType);
    int GetWasData () const;
    int GuessWasData (KTime* pStart = NULL, KTime* pStep = NULL);

    void KeyTangeantHide ();

    int GetUpdateId () const;
    int GetValuesUpdateId () const;

    void CallbackRegister (kFCurveCallback pCallback, void* pObject);
    void CallbackUnregister (kFCurveCallback pCallback, void* pObject);
    void CallbackEnable (bool pEnable);
    void CallbackClear ();

public:
	//! Automatically convert KFCURVE_INTERPOLATION_CUBIC type auto tangent key to Time-Independent.
	static bool sConvertAutoTimeIndepedent;

	/** Only For MotionBuilder and FbxSDK to fast data moving. 
	*	As of 2009-10-29, MotionBuilder and Fbx (Turnpike) has the same internal data structure for 
	*   KFCurve, KPriFCurveKey, KPriFCurveKeyAttr classes, we want to take advantage of this for
	*	Fast data moving between MotionBuilder and FbxSDK. If any internal data structure for those 
	*	class, we should come back here to make sure it's still working.
	*/
	void CopyExternalPriKeyAndAttr(void** pSourceFCurveKeysList, int pSourceFCurveKeyCount); 

	KPriFCurveKey** GetPriFCurveKeysList() const { return mFCurveKeysList; }

private:
	void KeyAttrSet(kFCurveIndex pKeyIndex, const KPriFCurveKeyAttr& pKeyAttr);

	/** Separate key attribute at the given index.
	* \remarks Result is undetermined if function curve has no key or index
	* is out of bounds.
	*/
	void KeyAttrSeparate(kFCurveIndex pKeyIndex);
	
	/** Inline lightweight function to check if the key has separate attribute, if not
	 * then call KeyAttrSeparate()
	 */
	KFBX_FCURVE_INLINE void KeyAttrSeparateCheck(kFCurveIndex pKeyIndex);

	/* Control optimization flag, when enable, we will perform KeyAttrShrink() operation
	 * when call KeyModifyEnd().
	 */ 
	void KeySetOptimizeEnable(bool pEnable); 
	void KeySetOptimizeThreshold(int pThreshold);

	/** Compress the keyAttr, let the key share the same instances of the attribute if 
	 * they have the same attribute value.
	 */
	void KeyAttrShrink(kFCurveIndex pStartIndex, kFCurveIndex pStopIndex);

    void IncrementUpdateId(int pInc);
    void CallbackAddEvent (int pWhat, int pIndexStart);

    int MapIndexAll (int pIndex, int &pWhere);
	void InitBuffers (int pKeyCount, bool pResetKeyCount = false );

    bool CheckCurve();
    void IsClamped( int pIndex, bool &pLeftClamped, bool &pRightClamped ) const; // Return true if the specified key is an auto clamp that is currently clamped

public:
	/** Static method to allocate and initialize global variables
	  * used for KFCurveKey attribute management.
	  * Must be called after the KFbxSdkManager is initialized.
	  */
	static void AllocateGlobals();

	/** Static method to delete global variables
	  * used for KFCurveKey attribute management.
	  * Must be called when the last KFbxSdkManager is deleted.
	  */
	static void FreeGlobals();

public:
	static	KFCurveKeyAttrManager*	mGlobalKeyAttrMemoryPool;
	// Recording Memory global var
	static	kULong					mGlobalRecordingMemory;
	static	KMemoryBlockQueue*		mGlobalKeyBufferQueue;

private:

    float mColor[3];

    kFCurveDouble mValue;

    int mUpdateId;
	int mFlags;
	int mOptimizationThreshold;
    int mKeyModifyGuard;

	KPriFCurveKey** mFCurveKeysList;

    int mFCurveKeyCount;	
    int mFCurveKeySize;	
    int mFCurveLastBlockIndex;	


    kUInt mPreExtrapolation;
    kULong mPreExtrapolationCount;
    kUInt mPostExtrapolation;
    kULong mPostExtrapolationCount;

    int mWasType;

    kFCurveIndex mLastSearchIndex;

    KTime mCandidateTime;
    kFCurveDouble mCandidateValue;

    KFCurveEvent mEvent;
    KArrayUL mCallbackFunctions;   // no delete on object must use array ul
    KArrayUL mCallbackObjects;	   // no delete on object must use array ul

	KFBX_FCURVE_INLINE KPriFCurveKey* InternalPriKeyGetPtr (kFCurveIndex pIndex) const;
    KFBX_FCURVE_INLINE KPriFCurveKeyAttr* InternalPriKeyAttrGetPtr(kFCurveIndex pIndex) const;

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS

};

// Allocate memory blocks for fcurve to give room for recording.
KFBX_DLL void KFCURVE_SetFCurveRecordMemoryBlockCount ( int pBlockCount );
KFBX_DLL int KFCURVE_GetFCurveMemoryBlockSize ( );
KFBX_DLL void KFCURVE_ClearMemoryBlockQueue ();

//
// class KFCurveEvent
//
KFBX_FCURVE_INLINE void KFCurveEvent::Clear () 
{
    mType = KFCURVEEVENT_NONE;
    mKeyIndexStart = mKeyIndexStop=-1; 
    mEventCount = 0; 
}


KFBX_FCURVE_INLINE void KFCurveEvent::Add (int pWhat, int pIndex) 
{		
    mType |= pWhat;
    mEventCount++;
    if ( (pIndex<mKeyIndexStart) || (mKeyIndexStart==-1)) 
    {
        mKeyIndexStart = pIndex;
    }
    if (pIndex>mKeyIndexStop) 
    {
        mKeyIndexStop = pIndex;
    }
}

//
//  class KFCurveKey
//
KFBX_FCURVE_INLINE KFCurveTangeantInfo::KFCurveTangeantInfo()
{
    mDerivative = 0.0;
    mWeight     = KFCURVE_DEFAULT_WEIGHT;
    mWeighted   = false;
    mVelocity	= KFCURVE_DEFAULT_VELOCITY;
    mHasVelocity= false;
    mAuto		= 0.0;
}

KFBX_FCURVE_INLINE KFCurveKey::KFCurveKey(const KPriFCurveKey& pKey, const KPriFCurveKeyAttr& pAttr)
{
	mTime = pKey.mTime;
	mValue = pKey.mValue;
	mFlags = pAttr.mFlags;
	mData[0] = pAttr.mData[0];
	mData[1] = pAttr.mData[1];
#ifdef KFCURVE_FLOAT
	mData[2] = pAttr.mData[2];
	mData[3] = pAttr.mData[3];
#else
	mWeight[0] = pAttr.mWeight[0];
	mWeight[1] = pAttr.mWeight[1];
	mVelocity[0] = pAttr.mVelocity[0];
	mVelocity[1] = pAttr.mVelocity[1];
#endif
}

KFBX_FCURVE_INLINE KPriFCurveKeyAttr KFCurveKey::GetKeyAttr() const
{
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.mFlags = mFlags;
	lKeyAttr.mData[0] = mData[0];
	lKeyAttr.mData[1] = mData[1];
#ifdef KFCURVE_FLOAT
	lKeyAttr.mData[2] = mData[2];
	lKeyAttr.mData[3] = mData[3];
#else
	lKeyAttr.mWeight[0] = mWeight[0];
	lKeyAttr.mWeight[1] = mWeight[1];
	lKeyAttr.mVelocity[0] = mVelocity[0];
	lKeyAttr.mVelocity[1] = mVelocity[1];
#endif
	return lKeyAttr;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::Set 
(
	kFCurveInterpolation pInterpolation /* = KFCURVE_INTERPOLATION_CUBIC*/, 
	kFCurveTangeantMode pTangeantMode /*= KFCURVE_TANGEANT_AUTO*/, 
	kFCurveDouble pData0 /*= 0*/, 
	kFCurveDouble pData1 /*= 0*/,
	kFCurveTangeantWeightMode pTangeantWeightMode /*= KFCURVE_WEIGHT_NONE*/, 
	kFCurveDouble pWeight0 /* = KFCURVE_DEFAULT_WEIGHT */,
	kFCurveDouble pWeight1 /* = KFCURVE_DEFAULT_WEIGHT */,
	kFCurveDouble pVelocity0 /* = KFCURVE_DEFAULT_VELOCITY */,
	kFCurveDouble pVelocity1 /* = KFCURVE_DEFAULT_VELOCITY */
)
{
	K_ASSERT (pInterpolation != KFCURVE_INTERPOLATION_CUBIC || pTangeantMode != KFCURVE_TANGEANT_TCB);

	SetInterpolation (pInterpolation);
	SetTangeantMode (pTangeantMode);
	SetDataDouble (KFCURVEKEY_RIGHT_SLOPE, pData0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_SLOPE, pData1);

	SetTangeantWeightMode (pTangeantWeightMode);
	SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, pWeight0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, pWeight1);

	SetDataDouble (KFCURVEKEY_RIGHT_VELOCITY, pVelocity0);
	SetDataDouble (KFCURVEKEY_NEXT_LEFT_VELOCITY, pVelocity1);

	SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);	
}

KFBX_FCURVE_INLINE void KPriFCurveKey::Set 
(
	KTime pTime, 
	kFCurveDouble pValue
)
{
	SetTime (pTime);
	SetValue (pValue);
}

//
//  class KFCurveKey
//

KFBX_FCURVE_INLINE void KFCurveKey::Set 
    (
    KTime pTime, 
    kFCurveDouble pValue, 
    kFCurveInterpolation pInterpolation /* = KFCURVE_INTERPOLATION_CUBIC*/, 
    kFCurveTangeantMode pTangeantMode /*= KFCURVE_TANGEANT_AUTO*/, 
    kFCurveDouble pData0 /*= 0*/, 
    kFCurveDouble pData1 /*= 0*/,
    kFCurveTangeantWeightMode pTangeantWeightMode /*= KFCURVE_WEIGHT_NONE*/, 
    kFCurveDouble pWeight0 /* = KFCURVE_DEFAULT_WEIGHT */,
    kFCurveDouble pWeight1 /* = KFCURVE_DEFAULT_WEIGHT */,
    kFCurveDouble pVelocity0 /* = KFCURVE_DEFAULT_VELOCITY */,
    kFCurveDouble pVelocity1 /* = KFCURVE_DEFAULT_VELOCITY */
    )
{
    K_ASSERT (pInterpolation != KFCURVE_INTERPOLATION_CUBIC || pTangeantMode != KFCURVE_TANGEANT_TCB);

    SetTime (pTime);
    SetValue (pValue);
    SetInterpolation (pInterpolation);
    SetTangeantMode (pTangeantMode);
    SetDataDouble (KFCURVEKEY_RIGHT_SLOPE, pData0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_SLOPE, pData1);

    SetTangeantWeightMode (pTangeantWeightMode);
    SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, pWeight0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, pWeight1);

    SetDataDouble (KFCURVEKEY_RIGHT_VELOCITY, pVelocity0);
    SetDataDouble (KFCURVEKEY_NEXT_LEFT_VELOCITY, pVelocity1);

    SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTCB (float pData1/*=0.0f*/, float pData2/*=0.0f*/, float pData3/*=0.0f*/)
{
	SetInterpolation (KFCURVE_INTERPOLATION_CUBIC);
	SetTangeantMode (KFCURVE_TANGEANT_TCB);
	SetDataFloat (KFCURVEKEY_TCB_TENSION, pData1);
	SetDataFloat (KFCURVEKEY_TCB_CONTINUITY, pData2);
	SetDataFloat (KFCURVEKEY_TCB_BIAS, pData3);
	SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTCB (KTime pTime, kFCurveDouble pValue, float pData1/*=0.0f*/, float pData2/*=0.0f*/, float pData3/*=0.0f*/)
{
    SetTime (pTime);
    SetValue (pValue);
    SetInterpolation (KFCURVE_INTERPOLATION_CUBIC);
    SetTangeantMode (KFCURVE_TANGEANT_TCB);
    SetDataFloat (KFCURVEKEY_TCB_TENSION, pData1);
    SetDataFloat (KFCURVEKEY_TCB_CONTINUITY, pData2);
    SetDataFloat (KFCURVEKEY_TCB_BIAS, pData3);
    SetTangeantVisibility (KFCURVE_TANGEANT_SHOW_NONE);
}


KFBX_FCURVE_INLINE void KFCurveKey::Set (KFCurveKey& iSource)
{
	memcpy(this, &iSource, sizeof(KFCurveKey));
}

KFBX_FCURVE_INLINE kFCurveInterpolation KPriFCurveKeyAttr::GetInterpolation() const
{
	return mFlags & KFCURVE_INTERPOLATION_ALL;
}

KFBX_FCURVE_INLINE kFCurveInterpolation KFCurveKey::GetInterpolation () const
{
    return mFlags & KFCURVE_INTERPOLATION_ALL;
}


KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetInterpolation (kFCurveInterpolation pInterpolation)	
{
    K_ASSERT_MSG(	(pInterpolation == KFCURVE_INTERPOLATION_CUBIC) || 
        (pInterpolation == KFCURVE_INTERPOLATION_LINEAR) ||
        (pInterpolation == KFCURVE_INTERPOLATION_CONSTANT) ,"Wrong interpolation type." );

    if( (((mFlags & KFCURVE_INTERPOLATION_ALL)!=KFCURVE_INTERPOLATION_CUBIC)) && pInterpolation == KFCURVE_INTERPOLATION_CUBIC )
    {
        // Clear weighting information
        SetTangeantWeightMode( KFCURVE_WEIGHTED_NONE);
        SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);
        SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);

        SetTangeantVelocityMode(KFCURVE_VELOCITY_NONE);
        SetDataDouble( KFCURVEKEY_RIGHT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
        SetDataDouble( KFCURVEKEY_NEXT_LEFT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
    }

    mFlags = (mFlags & ~KFCURVE_INTERPOLATION_ALL) | (pInterpolation & KFCURVE_INTERPOLATION_ALL); 
}


KFBX_FCURVE_INLINE void KFCurveKey::SetInterpolation (kFCurveInterpolation pInterpolation)	
{
	K_ASSERT_MSG(	(pInterpolation == KFCURVE_INTERPOLATION_CUBIC) || 
					(pInterpolation == KFCURVE_INTERPOLATION_LINEAR) ||
					(pInterpolation == KFCURVE_INTERPOLATION_CONSTANT) ,"Wrong interpolation type." );

	if( (((mFlags & KFCURVE_INTERPOLATION_ALL)!=KFCURVE_INTERPOLATION_CUBIC)) && pInterpolation == KFCURVE_INTERPOLATION_CUBIC )
	{
		// Clear weighting information
		SetTangeantWeightMode( KFCURVE_WEIGHTED_NONE);
		SetDataDouble (KFCURVEKEY_RIGHT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);
		SetDataDouble (KFCURVEKEY_NEXT_LEFT_WEIGHT, KFCURVE_DEFAULT_WEIGHT);

		SetTangeantVelocityMode(KFCURVE_VELOCITY_NONE);
		SetDataDouble( KFCURVEKEY_RIGHT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
		SetDataDouble( KFCURVEKEY_NEXT_LEFT_VELOCITY, KFCURVE_DEFAULT_VELOCITY);
	}

	mFlags = (mFlags & ~KFCURVE_INTERPOLATION_ALL) | (pInterpolation & KFCURVE_INTERPOLATION_ALL); 
}

KFBX_FCURVE_INLINE kFCurveConstantMode KPriFCurveKeyAttr::GetConstantMode() const
{
	return mFlags & KFCURVE_CONSTANT_ALL;
}

KFBX_FCURVE_INLINE kFCurveConstantMode KFCurveKey::GetConstantMode() const
{
    return mFlags & KFCURVE_CONSTANT_ALL;
}

KFBX_FCURVE_INLINE kFCurveTangeantMode KPriFCurveKeyAttr::GetTangeantMode( bool pIncludeOverrides ) const
{
    if( pIncludeOverrides )
    {
        return mFlags & KFCURVE_TANGEANT_ALL;
    }
    else
    {
        return mFlags & KFCURVE_TANGEANT_TYPE_MASK;
    }
}

KFBX_FCURVE_INLINE kFCurveTangeantMode KFCurveKey::GetTangeantMode( bool pIncludeOverrides ) const
{
	if( pIncludeOverrides )
	{
		return mFlags & KFCURVE_TANGEANT_ALL;
	}
	else
	{
		return mFlags & KFCURVE_TANGEANT_TYPE_MASK;
	}
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetConstantMode (kFCurveConstantMode pMode)			
{
    K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) ||
        (pMode == KFCURVE_CONSTANT_STANDARD) ||
        (pMode == KFCURVE_CONSTANT_NEXT),"Wrong constant mode.");

    mFlags = (mFlags & ~KFCURVE_CONSTANT_ALL) | (pMode & KFCURVE_CONSTANT_ALL); 
}

KFBX_FCURVE_INLINE void KFCurveKey::SetConstantMode (kFCurveConstantMode pMode)			
{
	K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) ||
					(pMode == KFCURVE_CONSTANT_STANDARD) ||
					(pMode == KFCURVE_CONSTANT_NEXT),"Wrong constant mode.");

	mFlags = (mFlags & ~KFCURVE_CONSTANT_ALL) | (pMode & KFCURVE_CONSTANT_ALL); 
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTangeantMode (kFCurveTangeantMode pTangeant, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)			
{
	K_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) || !(pTangeant & ~KFCURVE_TANGEANT_ALL), "Wrong tangeant mode." );
	K_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) || !(pTangeant & ~KFCURVE_CONSTANT_ALL), "Wrong tangeant mode." );

	// Convert Auto to Time-Independent.
	if (! pIgnoreAutoTimeIndepedentConversion && KFCurve::sConvertAutoTimeIndepedent && (mFlags & KFCURVE_INTERPOLATION_CUBIC) && (pTangeant & KFCURVE_TANGEANT_AUTO))
	{
		pTangeant = pTangeant | KFCURVE_GENERIC_TIME_INDEPENDENT;
	}

	mFlags = (mFlags & ~(KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL)) | (pTangeant & (KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL) ); 
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTangeantMode (kFCurveTangeantMode pTangeant, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)			
{
	K_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) || !(pTangeant & ~KFCURVE_TANGEANT_ALL), "Wrong tangeant mode." );
	K_ASSERT_MSG( (GetInterpolation() != KFCURVE_INTERPOLATION_CONSTANT) || !(pTangeant & ~KFCURVE_CONSTANT_ALL), "Wrong tangeant mode." );

	// Convert Auto to Time-Independent.
	if (! pIgnoreAutoTimeIndepedentConversion && KFCurve::sConvertAutoTimeIndepedent && (mFlags & KFCURVE_INTERPOLATION_CUBIC) && (pTangeant & KFCURVE_TANGEANT_AUTO))
	{
		pTangeant = pTangeant | KFCURVE_GENERIC_TIME_INDEPENDENT;
	}

    mFlags = (mFlags & ~(KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL)) | (pTangeant & (KFCURVE_TANGEANT_ALL|KFCURVE_CONSTANT_ALL) ); 
}

KFBX_FCURVE_INLINE kFCurveTangeantWeightMode KPriFCurveKeyAttr::GetTangeantWeightMode() const
{
    return mFlags & KFCURVE_WEIGHTED_ALL;
}

KFBX_FCURVE_INLINE kFCurveTangeantWeightMode KFCurveKey::GetTangeantWeightMode() const
{
	return mFlags & KFCURVE_WEIGHTED_ALL;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTangeantWeightMode(kFCurveTangeantWeightMode pTangent, kFCurveTangeantWeightMode pMask /* KFCURVE_WEIGHTED_ALL */ )
{
    pMask &= KFCURVE_WEIGHTED_ALL;
    mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTangeantWeightMode(kFCurveTangeantWeightMode pTangent, kFCurveTangeantWeightMode pMask /* KFCURVE_WEIGHTED_ALL */ )
{

	pMask &= KFCURVE_WEIGHTED_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode KPriFCurveKeyAttr::GetTangeantVelocityMode() const
{
	return mFlags & KFCURVE_VELOCITY_ALL;
}

KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode KFCurveKey::GetTangeantVelocityMode() const
{
	return mFlags & KFCURVE_VELOCITY_ALL;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight ) 
{
#ifdef KFCURVE_FLOAT
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData);
#else
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData, mWeight);
#endif
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTangentWeightAndAdjustTangent( EKFCurveDataIndex pIndex, kFCurveDouble pWeight ) 
{
#ifdef KFCURVE_FLOAT
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData);
#else
    TangentWeightAndAdjustTangent(pIndex, pWeight, mData, mWeight);
#endif
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangent, kFCurveTangeantVelocityMode pMask /* KFCURVE_VELOCITY_ALL */ )
{
	pMask &= KFCURVE_VELOCITY_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTangeantVelocityMode(kFCurveTangeantVelocityMode pTangent, kFCurveTangeantVelocityMode pMask /* KFCURVE_VELOCITY_ALL */ )
{
	pMask &= KFCURVE_VELOCITY_ALL;
	mFlags = (mFlags & ~pMask) | (pTangent & pMask); 
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetTangeantVisibility (kFCurveTangeantVisibility pVisibility)				
{
	K_ASSERT_MSG(	(pVisibility == KFCURVE_TANGEANT_SHOW_NONE) || 
		(pVisibility == KFCURVE_TANGEANT_SHOW_LEFT) ||
		(pVisibility == KFCURVE_TANGEANT_SHOW_RIGHT) ||
		(pVisibility == KFCURVE_TANGEANT_SHOW_BOTH) ,"Wrong visibility type." );
   
	mFlags = (mFlags & ~KFCURVE_TANGEANT_SHOW_BOTH) | (pVisibility & KFCURVE_TANGEANT_SHOW_BOTH); 
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTangeantVisibility (kFCurveTangeantVisibility pVisibility)				
{
    K_ASSERT_MSG(	(pVisibility == KFCURVE_TANGEANT_SHOW_NONE) || 
        (pVisibility == KFCURVE_TANGEANT_SHOW_LEFT) ||
        (pVisibility == KFCURVE_TANGEANT_SHOW_RIGHT) ||
        (pVisibility == KFCURVE_TANGEANT_SHOW_BOTH) ,"Wrong visibility type." );

    mFlags = (mFlags & ~KFCURVE_TANGEANT_SHOW_BOTH) | (pVisibility & KFCURVE_TANGEANT_SHOW_BOTH); 
}

KFBX_FCURVE_INLINE kFCurveTangeantVisibility KPriFCurveKeyAttr::GetTangeantVisibility ()  const
{
	return mFlags & KFCURVE_TANGEANT_SHOW_BOTH;
}

KFBX_FCURVE_INLINE kFCurveTangeantVisibility KFCurveKey::GetTangeantVisibility () const
{
    return mFlags & KFCURVE_TANGEANT_SHOW_BOTH;
}

KFBX_FCURVE_INLINE kFCurveDouble KPriFCurveKeyAttr::GetDataDouble (EKFCurveDataIndex pIndex)  const
{
	if( pIndex < KFCURVEKEY_WEIGHTS )
	{
		return mData[pIndex];
	}
	else
	{
		#ifdef KFCURVE_FLOAT
			return (kFCurveDouble)(((kInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS])/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
		#else		
			return (kFCurveDouble)mWeight[pIndex-KFCURVEKEY_WEIGHTS]/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
		#endif
	}
}

KFBX_FCURVE_INLINE kFCurveDouble KFCurveKey::GetDataDouble (EKFCurveDataIndex pIndex) const
{
    if( pIndex < KFCURVEKEY_WEIGHTS )
    {
        return mData[pIndex];
    }
    else
    {
        #ifdef KFCURVE_FLOAT
            return (kFCurveDouble)(((kInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS])/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
        #else		
            return (kFCurveDouble)mWeight[pIndex-KFCURVEKEY_WEIGHTS]/(kFCurveDouble)KFCURVE_WEIGHT_DIVIDER;
        #endif
    }
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetDataDouble (EKFCurveDataIndex pIndex, kFCurveDouble pValue) 
{
	if( pIndex < KFCURVEKEY_RIGHT_WEIGHT )
	{
		mData[pIndex] = pValue;
	}
	else
	{
		if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue > KFCURVE_MAX_WEIGHT )
		{
			pValue = KFCURVE_MAX_WEIGHT;
		}
		else if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue < KFCURVE_MIN_WEIGHT )
		{
			pValue = KFCURVE_MIN_WEIGHT;
		}

		#ifdef KFCURVE_FLOAT
			(((kInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS]) = (kInt16)(pValue*KFCURVE_WEIGHT_DIVIDER);
		#else		
			mWeight[pIndex-KFCURVEKEY_WEIGHTS] = pValue*KFCURVE_WEIGHT_DIVIDER;
		#endif
	}
}

KFBX_FCURVE_INLINE void KFCurveKey::SetDataDouble (EKFCurveDataIndex pIndex, kFCurveDouble pValue) 
{
    if( pIndex < KFCURVEKEY_RIGHT_WEIGHT )
    {
        mData[pIndex] = pValue;
    }
    else
    {
        if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue > KFCURVE_MAX_WEIGHT )
        {
            pValue = KFCURVE_MAX_WEIGHT;
        }
        else if( (pIndex == KFCURVEKEY_RIGHT_WEIGHT || pIndex == KFCURVEKEY_NEXT_LEFT_WEIGHT ) && pValue < KFCURVE_MIN_WEIGHT )
        {
            pValue = KFCURVE_MIN_WEIGHT;
        }

        #ifdef KFCURVE_FLOAT
            (((kInt16*)(&mData[KFCURVEKEY_WEIGHTS]))[pIndex-KFCURVEKEY_WEIGHTS]) = (kInt16)(pValue*KFCURVE_WEIGHT_DIVIDER);
        #else		
            mWeight[pIndex-KFCURVEKEY_WEIGHTS] = pValue*KFCURVE_WEIGHT_DIVIDER;
        #endif
    }
}

KFBX_FCURVE_INLINE float KPriFCurveKeyAttr::GetDataFloat (EKFCurveDataIndex pIndex)  const
{
	return ( (float *)&mData[0])[pIndex];
}

KFBX_FCURVE_INLINE float KFCurveKey::GetDataFloat (EKFCurveDataIndex pIndex)  const
{
    return ( (float *)&mData[0])[pIndex];
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetDataFloat (EKFCurveDataIndex pIndex, float pValue) 
{
	((float *)&mData[0])[pIndex] = pValue;
}

KFBX_FCURVE_INLINE void KFCurveKey::SetDataFloat (EKFCurveDataIndex pIndex, float pValue) 
{
    ((float *)&mData[0])[pIndex] = pValue;
}

KFBX_FCURVE_INLINE float* KPriFCurveKeyAttr::GetDataPtr() const
{
    return (float*)mData;
}

KFBX_FCURVE_INLINE float* KFCurveKey::GetDataPtr() const
{
	return (float*)mData;
}

KFBX_FCURVE_INLINE kFCurveDouble KPriFCurveKey::GetValue ()  const
{
    return mValue;
}

KFBX_FCURVE_INLINE kFCurveDouble KFCurveKey::GetValue ()  const
{
	return mValue;
}


KFBX_FCURVE_INLINE void KPriFCurveKey::SetValue (kFCurveDouble pValue) 
{
    mValue=pValue;
}

KFBX_FCURVE_INLINE void KFCurveKey::SetValue (kFCurveDouble pValue) 
{
	mValue=pValue;
}

KFBX_FCURVE_INLINE void KPriFCurveKey::IncValue (kFCurveDouble pValue) 
{
	mValue+=pValue;
}

KFBX_FCURVE_INLINE void KFCurveKey::IncValue (kFCurveDouble pValue) 
{
    mValue+=pValue;
}

KFBX_FCURVE_INLINE void KPriFCurveKey::MultValue (kFCurveDouble pValue) 
{
    mValue*=pValue;
}

KFBX_FCURVE_INLINE void KFCurveKey::MultValue (kFCurveDouble pValue) 
{
	mValue*=pValue;
}

KFBX_FCURVE_INLINE KTime KPriFCurveKey::GetTime ()  const
{
	return mTime;
}

KFBX_FCURVE_INLINE KTime KFCurveKey::GetTime () const
{
    return mTime;
}

KFBX_FCURVE_INLINE void KPriFCurveKey::SetTime (KTime pTime) 
{
	K_ASSERT_MSG( pTime != KTIME_MINUS_INFINITE && 
	pTime != KTIME_INFINITE, "Key at infinite!" );

	mTime=pTime;
}

KFBX_FCURVE_INLINE void KFCurveKey::SetTime (KTime pTime) 
{
    K_ASSERT_MSG( pTime != KTIME_MINUS_INFINITE && 
        pTime != KTIME_INFINITE, "Key at infinite!" );

    mTime=pTime;
}

KFBX_FCURVE_INLINE void KPriFCurveKey::IncTime (KTime pTime) 
{
	mTime+=pTime;
}

KFBX_FCURVE_INLINE void KFCurveKey::IncTime (KTime pTime) 
{
    mTime+=pTime;
}


KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetSelected (bool pSelected) 
{
    mFlags = pSelected ? (mFlags & ~KFCURVE_SELECT_ALL) | KFCURVE_SELECT_POINT : (mFlags & ~KFCURVE_SELECT_ALL);
}

KFBX_FCURVE_INLINE void KFCurveKey::SetSelected (bool pSelected) 
{
	mFlags = pSelected ? (mFlags & ~KFCURVE_SELECT_ALL) | KFCURVE_SELECT_POINT : (mFlags & ~KFCURVE_SELECT_ALL);
}

KFBX_FCURVE_INLINE bool KPriFCurveKeyAttr::GetSelected () const
{
    return (mFlags & KFCURVE_SELECT_POINT) ? true : false;
}

KFBX_FCURVE_INLINE bool KFCurveKey::GetSelected () const
{
	return (mFlags & KFCURVE_SELECT_POINT) ? true : false;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetMarkedForManipulation (bool pSelected) 
{
    mFlags = pSelected ? (mFlags & ~KFCURVE_MARKED_ALL) | KFCURVE_MARKED_FOR_MANIP : (mFlags & ~KFCURVE_MARKED_ALL);
}

KFBX_FCURVE_INLINE void KFCurveKey::SetMarkedForManipulation (bool pSelected) 
{
	mFlags = pSelected ? (mFlags & ~KFCURVE_MARKED_ALL) | KFCURVE_MARKED_FOR_MANIP : (mFlags & ~KFCURVE_MARKED_ALL);
}

KFBX_FCURVE_INLINE bool KPriFCurveKeyAttr::GetMarkedForManipulation () const
{
	return (mFlags & KFCURVE_MARKED_FOR_MANIP) ? true : false;
}

KFBX_FCURVE_INLINE bool KFCurveKey::GetMarkedForManipulation () const
{
    return (mFlags & KFCURVE_MARKED_FOR_MANIP) ? true : false;
}

KFBX_FCURVE_INLINE void KPriFCurveKey::Init()
{
    mValue = 0.0;
    mTime = KTIME_ZERO;
	mAttr = NULL;
}

KFBX_FCURVE_INLINE void KFCurveKey::Init()
{
    mValue = 0.0;
    mTime = KTIME_ZERO;
    mFlags = 0;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::SetBreak(bool pVal)
{
	K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
		(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
		(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
		(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
		(GetTangeantMode() == KFCURVE_TANGEANT_USER) ,"Wrong tangeant mode." );

	if(pVal)
		mFlags = mFlags |  KFCURVE_GENERIC_BREAK ;
	else
		mFlags = mFlags & ~KFCURVE_GENERIC_BREAK ;	

} 

KFBX_FCURVE_INLINE void KFCurveKey::SetBreak(bool pVal)
{
    K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
        (GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
        (GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
        (GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
        (GetTangeantMode() == KFCURVE_TANGEANT_USER) ,"Wrong tangent mode." );

    if(pVal)
        mFlags = mFlags |  KFCURVE_GENERIC_BREAK ;
    else
        mFlags = mFlags & ~KFCURVE_GENERIC_BREAK ;	

} 

KFBX_FCURVE_INLINE bool KPriFCurveKeyAttr::GetBreak() const
{
	K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
			(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_USER)  ,"Wrong tangent mode." );

    if( ((mFlags & KFCURVE_GENERIC_BREAK ) == KFCURVE_GENERIC_BREAK))
        return true;
    else
        return false; 

}

KFBX_FCURVE_INLINE bool KFCurveKey::GetBreak() const
{
	K_ASSERT_MSG(	(GetInterpolation() != KFCURVE_INTERPOLATION_CUBIC) ||					
			(GetTangeantMode() == KFCURVE_TANGEANT_BREAK) ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_AUTO_BREAK)  ||
			(GetTangeantMode() == KFCURVE_TANGEANT_USER)  ,"Wrong tangent mode." );

	if( ((mFlags & KFCURVE_GENERIC_BREAK ) == KFCURVE_GENERIC_BREAK))
		return true;
	else
		return false; 

}

KFBX_FCURVE_INLINE bool KPriFCurveKeyAttr::IsEqual(const KPriFCurveKeyAttr& pRsh) const
{
	// To Modify, don't need to check the data for some Flags. 
	return (this == &pRsh) ||
		mFlags == pRsh.mFlags &&
		mData[0] == pRsh.mData[0] &&
		mData[1] == pRsh.mData[1] &&
	#ifdef KFCURVE_FLOAT
		mData[2] == pRsh.mData[2] &&
		mData[3] == pRsh.mData[3];
	#else
		mWeight[0] == pRsh.mWeight[0] &&
		mWeight[1] == pRsh.mWeight[1] &&
		mVelocity[0] == pRsh.mVelocity[0] &&
		mVelocity[1] == pRsh.mVelocity[1];
	#endif
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::IncRefCount()
{
	++mRefCount;
}

KFBX_FCURVE_INLINE void KPriFCurveKeyAttr::DecRefCount()
{
	--mRefCount;
}

KFBX_FCURVE_INLINE kUInt32 KPriFCurveKeyAttr::GetRefCount() const
{
	return mRefCount;
}
//****************************************************************************************
// class KFCurve
//****************************************************************************************

KFBX_FCURVE_INLINE kFCurveDouble KFCurve::GetValue () const 
{
    return mValue;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
KFBX_FCURVE_INLINE void KFCurve::SetPreExtrapolation (kUInt pExtrapolation) 
{
    K_ASSERT_MSG(	(pExtrapolation == KFCURVE_EXTRAPOLATION_CONST) || 
        (pExtrapolation == KFCURVE_EXTRAPOLATION_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_MIRROR_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_KEEP_SLOPE) ,"Wrong extrapolation type." );

    mPreExtrapolation = pExtrapolation; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}
#endif

KFBX_FCURVE_INLINE kUInt KFCurve::GetPreExtrapolation () const 
{
    return mPreExtrapolation;
}


KFBX_FCURVE_INLINE void KFCurve::SetPreExtrapolationCount (kULong pCount) 
{
    mPreExtrapolationCount = pCount; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}


KFBX_FCURVE_INLINE kULong KFCurve::GetPreExtrapolationCount ()  const
{
    return mPreExtrapolationCount;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

KFBX_FCURVE_INLINE void KFCurve::SetPostExtrapolation (kUInt pExtrapolation) 
{
    K_ASSERT_MSG(	(pExtrapolation == KFCURVE_EXTRAPOLATION_CONST) || 
        (pExtrapolation == KFCURVE_EXTRAPOLATION_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_MIRROR_REPETITION) ||
        (pExtrapolation == KFCURVE_EXTRAPOLATION_KEEP_SLOPE) ,"Wrong extrapolation type." );

    mPostExtrapolation = pExtrapolation; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}

#endif

KFBX_FCURVE_INLINE kUInt KFCurve::GetPostExtrapolation () const 
{
    return mPostExtrapolation;
}


KFBX_FCURVE_INLINE void KFCurve::SetPostExtrapolationCount (kULong pCount) 
{
    mPostExtrapolationCount = pCount; 
    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, -1);
}


KFBX_FCURVE_INLINE kULong KFCurve::GetPostExtrapolationCount ()  const
{
    return mPostExtrapolationCount;
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
KFBX_FCURVE_INLINE KPriFCurveKey* KFCurve::InternalPriKeyGetPtr (int pIndex) const
{
    K_ASSERT_MSG( pIndex >= 0, "Negative indexes are not recommended." );
    K_ASSERT_MSG( mFCurveKeysList && mFCurveKeysList[pIndex / KEY_BLOCK_COUNT], "Accessing unallocated buffer." );

    return mFCurveKeysList[pIndex / KEY_BLOCK_COUNT] + (pIndex % KEY_BLOCK_COUNT);
}


KFBX_FCURVE_INLINE KPriFCurveKeyAttr* KFCurve::InternalPriKeyAttrGetPtr(kFCurveIndex pIndex) const
{
	#ifdef _DEBUG
		KPriFCurveKey* lKey = InternalPriKeyGetPtr(pIndex);
		K_ASSERT_MSG(lKey->mAttr != NULL, "Accessing uninitialized keyattr.");
		return lKey->mAttr;
	#else
		return InternalPriKeyGetPtr(pIndex)->mAttr;
	#endif
}
#endif // DOXYGEN_SHOULD_SKIP_THIS

/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/
/*********************************************************************************************/
KFBX_FCURVE_INLINE void KFCurve::KeySet 
    (
    kFCurveIndex pKeyIndex,
    KTime pTime, 
    kFCurveDouble pValue, 
    kFCurveInterpolation pInterpolation, 
    kFCurveTangeantMode pTangentMode, 
    kFCurveDouble pRightSlope, 
    kFCurveDouble pNextLeftSlope, 
    kFCurveTangeantWeightMode pTangentWeightMode, 
    kFCurveDouble pWeight0, 
    kFCurveDouble pWeight1, 
    kFCurveDouble pVelocity0, 
    kFCurveDouble pVelocity1
    )
{
	KPriFCurveKey *lPriKey = InternalPriKeyGetPtr(pKeyIndex);
	lPriKey->Set(pTime, pValue);
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.mFlags = 0;
    if (lPriKey->mAttr)
        lKeyAttr.mFlags = lPriKey->mAttr->mFlags;
	lKeyAttr.Set( pInterpolation, pTangentMode, pRightSlope, pNextLeftSlope, pTangentWeightMode, pWeight0, pWeight1, pVelocity0, pVelocity1);

	KeyAttrSet(pKeyIndex, lKeyAttr);
}

KFBX_FCURVE_INLINE void KFCurve::KeySetTCB 
    (
    kFCurveIndex pKeyIndex,
    KTime pTime, 
    kFCurveDouble pValue, 
    float pData0, 
    float pData1, 
    float pData2
    )
{
	InternalPriKeyGetPtr(pKeyIndex)->Set(pTime, pValue);
	KPriFCurveKeyAttr lKeyAttr;
	lKeyAttr.SetTCB(pData0, pData1, pData2);

	KeyAttrSet(pKeyIndex, lKeyAttr);
}

KFBX_FCURVE_INLINE kFCurveInterpolation KFCurve::KeyGetInterpolation(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetInterpolation();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetInterpolation(kFCurveIndex pKeyIndex, kFCurveInterpolation pInterpolation)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
	if (lKey->mAttr)
	{
        if ( lKey->mAttr->GetInterpolation() != pInterpolation)
        {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetInterpolation(pInterpolation);
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE kFCurveConstantMode KFCurve::KeyGetConstantMode(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetConstantMode();
}

KFBX_FCURVE_INLINE kFCurveTangeantMode KFCurve::KeyGetTangeantMode(kFCurveIndex pKeyIndex, bool pIncludeOverrides ) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantMode( pIncludeOverrides );
}

KFBX_FCURVE_INLINE kFCurveTangeantWeightMode KFCurve::KeyGetTangeantWeightMode(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantWeightMode();
}

KFBX_FCURVE_INLINE kFCurveTangeantVelocityMode KFCurve::KeyGetTangeantVelocityMode(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantVelocityMode();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetConstantMode(kFCurveIndex pKeyIndex, kFCurveConstantMode pMode)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
	if (lKey->mAttr)
    {
        if (lKey->mAttr->GetConstantMode() != pMode)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetConstantMode(pMode);
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE void KFCurve::KeySetTangeantMode(kFCurveIndex pKeyIndex, kFCurveTangeantMode pTangent, bool pIgnoreAutoTimeIndepedentConversion/* = false*/)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
        kUInt32 lFlags = lKey->mAttr->mFlags;
    	lKey->mAttr->SetTangeantMode(pTangent, pIgnoreAutoTimeIndepedentConversion); //only affect mFlags

	    if (lKey->mAttr->mFlags != lFlags)
	    {
		    if (lKey->mAttr->GetRefCount() > 1)
		    {
			    kUInt32 lSwapFlags = lKey->mAttr->mFlags;
			    lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
			    KeyAttrSeparate(pKeyIndex);
			    lKey->mAttr->mFlags = lSwapFlags;
		    }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE void KFCurve::KeySetTangeantWeightMode(kFCurveIndex pKeyIndex, kFCurveTangeantWeightMode pTangentWeightMode, kFCurveTangeantWeightMode pMask)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    kUInt32 lFlags = lKey->mAttr->mFlags;
	    lKey->mAttr->SetTangeantWeightMode(pTangentWeightMode, pMask); //only affect mFlags
	    if (lKey->mAttr->mFlags != lFlags)
	    {
	       if (lKey->mAttr->GetRefCount() > 1)
	       {
		      kUInt32 lSwapFlags = lKey->mAttr->mFlags;
		      lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
		      KeyAttrSeparate(pKeyIndex);
		      lKey->mAttr->mFlags = lSwapFlags;
	       }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE void KFCurve::KeySetTangeantVelocityMode(kFCurveIndex pKeyIndex, kFCurveTangeantVelocityMode pTangentVelocityMode, kFCurveTangeantVelocityMode pMask)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	// Avoid call expensive CallbackAddEvent() and KeyAttrSeparate(). 
	// We need to test if the flag value will be really changed.
	// but there is not easy way to tell that change for this operation,
	// so we need to performance special "try and swap" technique.
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    kUInt32 lFlags = lKey->mAttr->mFlags;
	    lKey->mAttr->SetTangeantVelocityMode(pTangentVelocityMode, pMask); //only affect mFlags
	    if (lKey->mAttr->mFlags != lFlags)
	    {
	       if (lKey->mAttr->GetRefCount() > 1)
	       {
		      kUInt32 lSwapFlags = lKey->mAttr->mFlags;
		      lKey->mAttr->mFlags = lFlags; //Restore previous attr flag for other keys.
		      KeyAttrSeparate(pKeyIndex);
		      lKey->mAttr->mFlags = lSwapFlags;
	       }
		    CallbackAddEvent (KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE kFCurveDouble KFCurve::KeyGetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataDouble(pIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeySetDataDouble(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, kFCurveDouble pValue)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetDataDouble(pIndex) != pValue)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetDataDouble(pIndex, pValue);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE float KFCurve::KeyGetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataFloat(pIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeySetDataFloat(kFCurveIndex pKeyIndex, EKFCurveDataIndex pIndex, float pValue)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetDataFloat(pIndex) != pValue)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetDataFloat(pIndex, pValue);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE const float* KFCurve::KeyGetDataPtr(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetDataPtr();
}

KFBX_FCURVE_INLINE kFCurveDouble KFCurve::KeyGetValue(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyGetPtr(pKeyIndex)->GetValue();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
	InternalPriKeyGetPtr(pKeyIndex)->SetValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeyIncValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->IncValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeyMultValue(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->MultValue(pValue);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITVALUE, pKeyIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeyMultTangeant(kFCurveIndex pKeyIndex, kFCurveDouble pValue)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	if (pValue == 1.0)
	{
       return;
	}
	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex); K_ASSERT(lKey->mAttr != NULL);
    KPriFCurveKey* lKeyNext = NULL;
    if (pKeyIndex < KeyGetCount()-1)
    {
        lKeyNext = InternalPriKeyGetPtr(pKeyIndex+1); 
        K_ASSERT(lKeyNext->mAttr != NULL);
    }

    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetInterpolation() == KFCURVE_INTERPOLATION_CUBIC)
	    {
            bool lScaleNextLeft = false;
		    switch (lKey->mAttr->GetTangeantMode())
		    {					
		    case KFCURVE_TANGEANT_USER:
		    case KFCURVE_TANGEANT_BREAK:
                lScaleNextLeft = true;
			    KeyAttrSeparateCheck(pKeyIndex);						
			    lKey->mAttr->SetDataDouble(KFCURVEKEY_RIGHT_SLOPE, lKey->mAttr->GetDataDouble(KFCURVEKEY_RIGHT_SLOPE) * pValue);

            case KFCURVE_TANGEANT_AUTO:
		    case KFCURVE_TANGEANT_AUTO_BREAK:
                if (lKeyNext)
                {
                    switch (lKeyNext->mAttr->GetTangeantMode())
                    {
                    case KFCURVE_TANGEANT_USER:
                    case KFCURVE_TANGEANT_BREAK:                    
                        lScaleNextLeft = true;
                    }
                }

                if (lScaleNextLeft)
                {
                    lKey->mAttr->SetDataDouble(KFCURVEKEY_NEXT_LEFT_SLOPE, lKey->mAttr->GetDataDouble(KFCURVEKEY_NEXT_LEFT_SLOPE) * pValue);
			        CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
                }
			    break;

		    case KFCURVE_TANGEANT_TCB:
			    // dunno how to handle this
		    default:
			    // nothing to do
			    break;
		    }
	    }
    }
}

KFBX_FCURVE_INLINE KTime KFCurve::KeyGetTime(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyGetPtr(pKeyIndex)->GetTime();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetTime(kFCurveIndex pKeyIndex, KTime pTime)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->SetTime(pTime);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITTIME, pKeyIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeyIncTime(kFCurveIndex pKeyIndex, KTime pTime)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	InternalPriKeyGetPtr(pKeyIndex)->IncTime(pTime);
    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITTIME, pKeyIndex);
}

KFBX_FCURVE_INLINE void KFCurve::KeySetSelected(kFCurveIndex pKeyIndex, bool pSelected)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetSelected() != pSelected)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetSelected(pSelected);
		    CallbackAddEvent(KFCURVEEVENT_SELECTION, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE bool KFCurve::KeyGetSelected(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetSelected();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetMarkedForManipulation(kFCurveIndex pKeyIndex, bool pMarked)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetMarkedForManipulation() != pMarked)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetMarkedForManipulation(pMarked);
	    }
    }
}

KFBX_FCURVE_INLINE bool KFCurve::KeyGetMarkedForManipulation(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetMarkedForManipulation();
}

KFBX_FCURVE_INLINE void	KFCurve::KeySetTangeantVisibility (kFCurveIndex pKeyIndex, kFCurveTangeantVisibility pVisibility)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);	
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {
	    if (lKey->mAttr->GetTangeantVisibility() != pVisibility)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetTangeantVisibility(pVisibility);
		    CallbackAddEvent(KFCURVEEVENT_SELECTION, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE kFCurveTangeantVisibility KFCurve::KeyGetTangeantVisibility (kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

    return InternalPriKeyAttrGetPtr(pKeyIndex)->GetTangeantVisibility();
}

KFBX_FCURVE_INLINE void KFCurve::KeySetBreak(kFCurveIndex pKeyIndex, bool pVal)
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	KPriFCurveKey* lKey = InternalPriKeyGetPtr(pKeyIndex);
    K_ASSERT(lKey->mAttr != NULL);
    if (lKey->mAttr)
    {	
        if (lKey->mAttr->GetBreak() != pVal)
	    {
		    KeyAttrSeparateCheck(pKeyIndex);
		    lKey->mAttr->SetBreak(pVal);
		    CallbackAddEvent(KFCURVEEVENT_KEY | KFCURVEEVENT_EDITOTHER, pKeyIndex);
	    }
    }
}

KFBX_FCURVE_INLINE bool KFCurve::KeyGetBreak(kFCurveIndex pKeyIndex) const
{
    K_ASSERT(pKeyIndex >= 0);
    K_ASSERT(pKeyIndex < KeyGetCount());

	return InternalPriKeyAttrGetPtr(pKeyIndex)->GetBreak();
}

KFBX_FCURVE_INLINE void KFCurve::KeyAttrSeparateCheck(kFCurveIndex pKeyIndex)
{
	KPriFCurveKeyAttr* lCurKeyAttr = InternalPriKeyAttrGetPtr(pKeyIndex);
	if (! lCurKeyAttr || lCurKeyAttr->GetRefCount() > 1 )
		KeyAttrSeparate(pKeyIndex);
}


/**	Create a function curve.
*/
KFBX_DLL HKFCurve KFCurveCreate();

// Create a function curve, FBX SDK internal use only.
KFBX_DLL HKFCurve KFCurveCreate(KFbx* pFbx, bool pOnlyDefaults = false, bool pColor = false);

// Create a function curve, FBX SDK internal use only.
KFBX_DLL HKFCurve KFCurveCreate(KFbx* pFbx, HKFCurve pCurve, bool pOnlyDefaults = false, bool pColor = false);

#include <fbxfilesdk/fbxfilesdk_nsend.h>


#endif // FBXFILESDK_COMPONENTS_KFCURVE_KFCURVE_H

