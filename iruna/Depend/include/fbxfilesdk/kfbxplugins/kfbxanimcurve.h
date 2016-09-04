/*!  \file kfbxanimcurve.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVE_H
#define FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVE_H

/**************************************************************************************

 Copyright (C) 2009 - 2010 Autodesk, Inc. and/or its licensors.
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

#include <fbxfilesdk/components/kfcurve/kfcurve.h>
#include <fbxfilesdk/kfbxplugins/kfbxanimcurvebase.h>
#include <fbxfilesdk/kfbxplugins/kfbxobject.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

/** This is the base class interface for the Fbx animation function curves keys.
  * \nosubgrouping
  * This class, for the time being, is implemented by the old KFCurveKey
  * structure. However, in a near future (2009-2010), KFbxAnimCurveKey will become the
  * main animation key object of the SDK, and the implementation
  * is subject to change.
  */

class KFbxAnimCurveDef {

public:
	static const int   kWEIGHT_DIVIDER = 9999; // precise enough and can be divided by 3 without error
	static const float kDEFAULT_WEIGHT;
	static const float kMIN_WEIGHT;
	static const float kMAX_WEIGHT;
	static const float kDEFAULT_VELOCITY;

	/** \enum ETangentMode Tangent modes.
	  * - \e eTANGENT_AUTO						Spline cardinal.
	  * - \e eTANGENT_TCB						Spline TCB (Tangent/Continuity/Bias).
	  * - \e eTANGENT_USER						Next slope at the left equal to slope at the right.
	  * - \e eTANGENT_BREAK						Independent left and right slopes.
	  * - \e eTANGENT_AUTO_BREAK				Combination of eTANGENT_AUTO and eTANGENT_BREAK.
	  * - \e eTANGENT_GENERIC_CLAMP				Auto key should be flat if next or previous keys have same value.
	  * - \e eTANGENT_GENERIC_TIME_INDEPENDENT	Auto key time independent.
	  */
	typedef enum {
		eTANGENT_AUTO                     = KFCURVE_TANGEANT_AUTO,
		eTANGENT_TCB                      = KFCURVE_TANGEANT_TCB,
		eTANGENT_USER                     = KFCURVE_TANGEANT_USER,
		eTANGENT_BREAK                    = KFCURVE_TANGEANT_BREAK,
		eTANGENT_AUTO_BREAK               = KFCURVE_TANGEANT_AUTO_BREAK,
		eTANGENT_GENERIC_CLAMP            = KFCURVE_GENERIC_CLAMP,
		eTANGENT_GENERIC_TIME_INDEPENDENT = KFCURVE_GENERIC_TIME_INDEPENDENT

	} ETangentMode;

	/** \enum EInterpolationType Interpolation modes.
	  * - \e eINTERPOLATION_CONSTANT	Constant value until next key.
	  * - \e eINTERPOLATION_LINEAR		Linear progression to next key.
	  * - \e eINTERPOLATION_CUBIC		Cubic progression to next key.
	  * - \e eINTERPOLATION_ALL
	  */
	typedef enum {
		eINTERPOLATION_CONSTANT = KFCURVE_INTERPOLATION_CONSTANT,
		eINTERPOLATION_LINEAR   = KFCURVE_INTERPOLATION_LINEAR,
		eINTERPOLATION_CUBIC    = KFCURVE_INTERPOLATION_CUBIC,
		eINTERPOLATION_ALL      = KFCURVE_INTERPOLATION_ALL
	} EInterpolationType;

    /** \enum EWeightedMode Weight modes.
      * - \e eWEIGHTED_NONE 
      * - \e eWEIGHTED_RIGHT
      * - \e eWEIGHTED_NEXT_LEFT
      * - \e eWEIGHTED_ALL
      */
    typedef enum {
        eWEIGHTED_NONE      = KFCURVE_WEIGHTED_NONE,
        eWEIGHTED_RIGHT     = KFCURVE_WEIGHTED_RIGHT,
        eWEIGHTED_NEXT_LEFT = KFCURVE_WEIGHTED_NEXT_LEFT,
        eWEIGHTED_ALL       = KFCURVE_WEIGHTED_ALL
    } EWeightedMode;

    /** \enum EConstantMode Key constant mode.
      * - \e eCONSTANT_STANDARD
      * - \e eCONSTANT_NEXT
      * - \e eCONSTANT_ALL
      */
    typedef enum {
        eCONSTANT_STANDARD  = KFCURVE_CONSTANT_STANDARD,
        eCONSTANT_NEXT      = KFCURVE_CONSTANT_NEXT,
        eCONSTANT_ALL       = KFCURVE_CONSTANT_ALL
    } EConstantMode;

	typedef enum {
		eVELOCITY_NONE	=		KFCURVE_VELOCITY_NONE,
		eVELOCITY_RIGHT	=		KFCURVE_VELOCITY_RIGHT,
		eVELOCITY_NEXT_LEFT =	KFCURVE_VELOCITY_NEXT_LEFT,
		eVELOCITY_ALL		=	KFCURVE_VELOCITY_ALL
	} EVelocityMode;

	typedef enum {
		eTANGENT_SHOW_NONE		= KFCURVE_TANGEANT_SHOW_NONE,
		eTANGENT_SHOW_LEFT		= KFCURVE_TANGEANT_SHOW_LEFT,
		eTANGENT_SHOW_RIGHT		= KFCURVE_TANGEANT_SHOW_RIGHT,
		eTANGENT_SHOW_BOTH		= KFCURVE_TANGEANT_SHOW_BOTH
	} ETangentVisibility;

	typedef enum {
		// User and Break tangent mode (data are float).
		eRIGHT_SLOPE			= KFCURVEKEY_RIGHT_SLOPE, 
		eNEXT_LEFT_SLOPE		= KFCURVEKEY_NEXT_LEFT_SLOPE, 

		// User and Break tangent break mode (data are kInt16 tokens from weight and converted to float).
		eWEIGHTS				= KFCURVEKEY_WEIGHTS, 
		eRIGHT_WEIGHT			= KFCURVEKEY_RIGHT_WEIGHT, 
		eNEXT_LEFT_WEIGHT		= KFCURVEKEY_NEXT_LEFT_WEIGHT, 

		// Velocity mode
		eVELOCITY				= KFCURVEKEY_VELOCITY,
		eRIGHT_VELOCITY			= KFCURVEKEY_RIGHT_VELOCITY,
		eNEXT_LEFT_VELOCITY		= KFCURVEKEY_NEXT_LEFT_VELOCITY, 

		// TCB tangent mode (data are floats).
		eTCB_TENSION			= KFCURVEKEY_TCB_TENSION, 
		eTCB_CONTINUITY			= KFCURVEKEY_TCB_CONTINUITY, 
		eTCB_BIAS				= KFCURVEKEY_TCB_BIAS,

	} EKFbxAnimCurveDataIndex;
};

/** Interface for animation key objects.
  * \nosubgrouping
  *
  * Users always use KFbxAnimCurveKey. A KFbxAnimCurveKey points to a KFbxAnimCurveKeyImpl.
  * See KFbxAnimCurveKFCurveKey for an example of implemented class.
  */
class KFBX_DLL KFbxAnimCurveKeyImpl
{
public:
    /** destructor.
      */
    virtual ~KFbxAnimCurveKeyImpl() {};

	/** Assignment operator.
	  */
    virtual KFbxAnimCurveKeyImpl& operator=(const KFbxAnimCurveKeyImpl& pFKey) = 0;

    /** Set time and value of key.
      * \param pTime New time of this key.
      * \param pValue New value of this key.
      */
	virtual void Set(KTime pTime, float pValue) = 0;

	/**	Set a key with cubic interpolation, TCB tangent mode.
	  *	\param pTime	Key time.
	  *	\param pValue	Key value.
	  *	\param pData0	Tension.
	  *	\param pData1	Continuity.
	  *	\param pData2	Bias.
	  */
	virtual void SetTCB(KTime pTime, float pValue, float pData0 = 0.0f, float pData1 = 0.0f, float pData2 = 0.0f) = 0;

    /** Get key value.
    *	\return Key value.
    */
    virtual float GetValue() const = 0;

	/** Set key value.
	  * \param pValue Key value to set.
	  */
	virtual void SetValue(float pValue) = 0;

    /** Get key interpolation.
    *	\return Key interpolation.
    */
    virtual KFbxAnimCurveDef::EInterpolationType GetInterpolation() const = 0;

	/** Set key interpolation.
	  * \param pInterpolation Interpolation type to set.
	  */
	virtual void SetInterpolation (KFbxAnimCurveDef::EInterpolationType pInterpolation) = 0;

	/** Get tangent mode.
    *	\return Tangent mode.
    */
    virtual KFbxAnimCurveDef::ETangentMode GetTangentMode(bool pIncludeOverrides = false) const = 0;

	/** Set tangent mode.
	  * \param pTangentMode Tangent mode to set.
	  */
	virtual void SetTangentMode (KFbxAnimCurveDef::ETangentMode pTangentMode) = 0;

	/** Get key tangent weight mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_WEIGHTED_NONE,
	*								KFCURVE_WEIGHTED_RIGHT,
	*								KFCURVE_WEIGHTED_NEXT_LEFT,
	*								KFCURVE_WEIGHTED_ALL
	*/
	virtual KFbxAnimCurveDef::EWeightedMode GetTangentWeightMode() const = 0;

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
	virtual void SetTangentWeightMode(KFbxAnimCurveDef::EWeightedMode pTangentWeightMode, KFbxAnimCurveDef::EWeightedMode pMask = KFbxAnimCurveDef::eWEIGHTED_ALL ) = 0;

	/** Get key tangent velocity mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_VELOCITY_NONE,
	*								KFCURVE_VELOCITY_RIGHT,
	*								KFCURVE_VELOCITY_NEXT_LEFT,
	*								KFCURVE_VELOCITY_ALL
	*/
	virtual KFbxAnimCurveDef::EVelocityMode GetTangentVelocityMode() const = 0;

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
	virtual void SetTangentVelocityMode(KFbxAnimCurveDef::EVelocityMode pTangentVelocityMode, KFbxAnimCurveDef::EVelocityMode pMask = KFbxAnimCurveDef::eVELOCITY_ALL ) = 0;

	/** Get key constant mode.
	*	Warning: This method is meaningful for constant interpolation only.
	*			 Using this method for non constant interpolated key will return unpredicted value.
	* Constant modes are:		KFCURVE_CONSTANT_STANDARD
	*							KFCURVE_CONSTANT_NEXT
	*	\return Key constant mode.
	*/
	virtual KFbxAnimCurveDef::EConstantMode GetConstantMode() const = 0;

	/** Set constant mode.
	  * \param pMode Constant mode to set.
	  */
	virtual void SetConstantMode(KFbxAnimCurveDef::EConstantMode pMode) = 0;

	/** Get data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \return Data value.
	  */
	virtual float GetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex) const = 0;

	/** Set data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \param pValue Data value to set.
	  */
	virtual void SetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex, float pValue) = 0;

	/** Set tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pVisibility	Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*						          KFCURVE_TANGEANT_SHOW_LEFT
	*						          KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	virtual void	SetTangentVisibility (KFbxAnimCurveDef::ETangentVisibility pVisibility) = 0;	

	/** Return tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\return Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*			                      KFCURVE_TANGEANT_SHOW_LEFT
	*			                      KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	virtual KFbxAnimCurveDef::ETangentVisibility GetTangentVisibility () const = 0;

	/** Set/Unset Break tangent
	* Only valid for User and Auto keys
	* \param pVal The break flag.
	*/
	virtual void SetBreak(bool pVal) = 0; 

	/** Get if tangent is break
	* Only valid for User and Auto keys
	*/
	virtual bool GetBreak() const = 0; 
};

class KFBX_DLL KFbxAnimCurveKey : public KFbxAnimCurveKeyBase
{

public:

	/** Constructor with no argument
	  */
	KFbxAnimCurveKey() : KFbxAnimCurveKeyBase()
    {
		K_ASSERT(mAllocatorFct != NULL);
		mImpl = (*mAllocatorFct)();
    }

	/** Constructor with time.
      * \param pTime The time of key.
      */
    KFbxAnimCurveKey(KTime pTime) : KFbxAnimCurveKeyBase()
    {
		K_ASSERT(mAllocatorFct != NULL);
		mImpl = (*mAllocatorFct)();
        SetTime(pTime);
    }

    /** Constructor with time and value.
      * \param pTime The time of key.
      * \param pVal The value of key.
      */
    KFbxAnimCurveKey(KTime pTime, float pVal) : KFbxAnimCurveKeyBase()
    {
		K_ASSERT(mAllocatorFct != NULL);
		mImpl = (*mAllocatorFct)();
        Set(pTime, pVal);
    }

	/** Copy constructor
	  */
	KFbxAnimCurveKey(KFbxAnimCurveKey const& pFKey) : KFbxAnimCurveKeyBase()
    {
		K_ASSERT(mCopyAllocatorFct != NULL);
		SetTime(pFKey.GetTime());
		mImpl = mCopyAllocatorFct(pFKey.GetImpl());
    }

	/** Destructor
	  */
	~KFbxAnimCurveKey()
    {
		K_ASSERT(mDeallocatorFct != NULL);
		(*mDeallocatorFct)(mImpl);
    }

    /** Assignment operator
      */
    KFbxAnimCurveKey& operator=(const KFbxAnimCurveKey& pFKey)
	{
		K_ASSERT(mImpl);
		if (mImpl)
		{
			*mImpl = *(pFKey.GetImpl());
		}
		SetTime(pFKey.GetTime());
		return *this;
	}

    /** Get time value.
    * \return Time value.
    */
    KTime GetTime() const
	{
		return KFbxAnimCurveKeyBase::GetTime();
	}

    /** Set time value.
    * \param pTime Time value to set.
    */
    void SetTime(const KTime& pTime)
	{
		KFbxAnimCurveKeyBase::SetTime(pTime);
	}

    /** Set time and value of key.
      * \param pTime New time of this key.
      * \param pValue New value of this key.
      */
	void Set(KTime pTime, float pValue)
	{
		KFbxAnimCurveKeyBase::SetTime(pTime);
		mImpl->Set(pTime, pValue);
	}

	/**	Set a key with cubic interpolation, TCB tangent mode.
	  *	\param pTime	Key time.
	  *	\param pValue	Key value.
	  *	\param pData0	Tension.
	  *	\param pData1	Continuity.
	  *	\param pData2	Bias.
	  */
	void SetTCB(KTime pTime, float pValue, float pData0 = 0.0f, float pData1 = 0.0f, float pData2 = 0.0f)
	{
		KFbxAnimCurveKeyBase::SetTime(pTime);
		mImpl->SetTCB(pTime, pValue, pData0, pData1, pData2);
	}

    /** Get key value.
    *	\return Key value.
    */
    float GetValue() const
	{
		return mImpl->GetValue();
	}

	/** Set key value.
	  * \param pValue Key value to set.
	  */
	void SetValue(float pValue)
	{
		mImpl->SetValue(pValue);
	}

	/** Get key interpolation.
    *	\return Key interpolation.
    */
    KFbxAnimCurveDef::EInterpolationType GetInterpolation()
	{
		return mImpl->GetInterpolation();
	}

	/** Set key interpolation.
	  * \param pInterpolation Interpolation type to set.
	  */
	void SetInterpolation (KFbxAnimCurveDef::EInterpolationType pInterpolation)
	{
		mImpl->SetInterpolation(pInterpolation);
	}

	/** Get tangent mode.
    *	\return Tangent mode.
    */
    KFbxAnimCurveDef::ETangentMode GetTangentMode(bool pIncludeOverrides = false)
	{
		return mImpl->GetTangentMode(pIncludeOverrides);
	}

	/** Set tangent mode.
	  * \param pTangentMode Tangent mode to set.
	  */
	void SetTangentMode (KFbxAnimCurveDef::ETangentMode pTangentMode)
	{
		mImpl->SetTangentMode(pTangentMode);
	}

	/** Get key tangent weight mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_WEIGHTED_NONE,
	*								KFCURVE_WEIGHTED_RIGHT,
	*								KFCURVE_WEIGHTED_NEXT_LEFT,
	*								KFCURVE_WEIGHTED_ALL
	*/
	KFbxAnimCurveDef::EWeightedMode GetTangentWeightMode() const
	{
		return mImpl->GetTangentWeightMode();
	}

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
	void SetTangentWeightMode(KFbxAnimCurveDef::EWeightedMode pTangentWeightMode, KFbxAnimCurveDef::EWeightedMode pMask = KFbxAnimCurveDef::eWEIGHTED_ALL )
	{
		mImpl->SetTangentWeightMode(pTangentWeightMode, pMask);
	}


	/** Get key tangent velocity mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	Tangent weight modes are:	KFCURVE_VELOCITY_NONE,
	*								KFCURVE_VELOCITY_RIGHT,
	*								KFCURVE_VELOCITY_NEXT_LEFT,
	*								KFCURVE_VELOCITY_ALL
	*/
	KFbxAnimCurveDef::EVelocityMode GetTangentVelocityMode() const
	{
		return mImpl->GetTangentVelocityMode();
	}

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
	void SetTangentVelocityMode(KFbxAnimCurveDef::EVelocityMode pTangentVelocityMode, KFbxAnimCurveDef::EVelocityMode pMask = KFbxAnimCurveDef::eVELOCITY_ALL )
	{
		mImpl->SetTangentVelocityMode(pTangentVelocityMode, pMask);
	}

	/** Get key constant mode.
	*	Warning: This method is meaningful for constant interpolation only.
	*			 Using this method for non constant interpolated key will return unpredicted value.
	* Constant modes are:		KFCURVE_CONSTANT_STANDARD
	*							KFCURVE_CONSTANT_NEXT
	*	\return Key constant mode.
	*/
	KFbxAnimCurveDef::EConstantMode GetConstantMode() const
	{
		return mImpl->GetConstantMode();
	}

	/** Set constant mode.
	  * \param pMode Constant mode to set.
	  */
	void SetConstantMode(KFbxAnimCurveDef::EConstantMode pMode)
	{
		mImpl->SetConstantMode(pMode);
	}

	/** Get data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \return Data value.
	  */
	float GetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex) const
	{
		return mImpl->GetDataFloat(pIndex);
	}

	/** Set data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \param pValue Data value to set.
	  */
	void SetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex, float pValue)
	{
		mImpl->SetDataFloat(pIndex, pValue);
	}

	/** Set tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\param pVisibility	Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*						          KFCURVE_TANGEANT_SHOW_LEFT
	*						          KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	void	SetTangentVisibility (KFbxAnimCurveDef::ETangentVisibility pVisibility)
	{
		mImpl->SetTangentVisibility(pVisibility);
	}

	/** Return tangent visibility mode.
	*	Warning: This method is meaningful for cubic interpolation only.
	*	\return Tangent visibility mode.
	*	Tangent visibility modes are: KFCURVE_TANGEANT_SHOW_NONE
	*			                      KFCURVE_TANGEANT_SHOW_LEFT
	*			                      KFCURVE_TANGEANT_SHOW_RIGHT
	*/
	KFbxAnimCurveDef::ETangentVisibility GetTangentVisibility () const
	{
		return mImpl->GetTangentVisibility();
	}

	/** Set/Unset Break tangent
	* Only valid for User and Auto keys
	* \param pVal The break flag.
	*/
	void SetBreak(bool pVal)
	{
		mImpl->SetBreak(pVal);
	}

	/** Get if tangent is break
	* Only valid for User and Auto keys
	*/
	bool GetBreak() const
	{
		return mImpl->GetBreak();
	}

	/** Get key implementation.
      * \return Pointer to implemented instance, e.g. a KFbxAnimCurveKFCurveKey.
      */
	KFbxAnimCurveKeyImpl* GetImpl() const
	{
		return mImpl;
	}

	/** Set allocator function
      * \param pAllocatorFct Allocator function
      */
	static void SetAllocatorFct(KFbxAnimCurveKeyImpl* (*pAllocatorFct)());

	/** Set copy allocator function
      * \param pCopy AllocatorFct Copy allocator function
      */
	static void SetCopyAllocatorFct(KFbxAnimCurveKeyImpl* (*pCopyAllocatorFct)(KFbxAnimCurveKeyImpl*));

	/** Set deallocator function
      * \param pDeallocatorFct Deallocator function
      */
	static void SetDeallocatorFct(void (*pDeallocatorFct)(KFbxAnimCurveKeyImpl*));

private:
	static KFbxAnimCurveKeyImpl* (*mAllocatorFct)();
	static KFbxAnimCurveKeyImpl* (*mCopyAllocatorFct)(KFbxAnimCurveKeyImpl*);
	static void (*mDeallocatorFct)(KFbxAnimCurveKeyImpl*);
	KFbxAnimCurveKeyImpl* mImpl;
};



/** This is the base class implementing the Fbx animation function curves.
  * \nosubgrouping
  * This class, for the time being, encapsulates the old KFCurve
  * structure. However, in a near future, this will become the
  * main animation curve object of the SDK and the implementation
  * is subject to change.
  */
class KFbxScene;
class KFBX_DLL KFbxAnimCurve : public KFbxAnimCurveBase
{
    KFBXOBJECT_DECLARE_ABSTRACT(KFbxAnimCurve, KFbxAnimCurveBase);

public:

    static KFbxAnimCurve* Create(KFbxScene* pContainer, char const *pName);

    /**
      * \name Key management.
      *
      */
    //@{
        /** Resize curve buffer to hold a certain number of key.
          * \param pKeyCount Number of key the curve will eventually hold.
          */
        virtual void ResizeKeyBuffer(int pKeyCount) = 0;

        /** Call this function prior to modifying the keys of this curve.
          * \remarks Be sure to call KFbxAnimCurve::KeyModifyEnd() after modification 
          *         of the keys are completed.
          */
        virtual void KeyModifyBegin () = 0;
        
        /** Call this function after modification of the keys of this curve.
          * \remarks You need to call KFbxAnimCurve::KeyModifyBegin() prior to modifying 
          *         the keys.
          */
        virtual void KeyModifyEnd () = 0;

        //! Remove all the keys and free buffer memory.
        virtual void KeyClear () = 0;

        /** Get the number of keys.
          * \return Key count.
          */
        virtual int KeyGetCount () const = 0;

        /** Add a key at given time.
          * Function KFbxAnimCurve::KeyInsert() SHOULD be used instead if the key 
          * is to be added in the curve and not at the end. This function does not
          * respect the interpolation type and tangents of the neighboring keys. 
          * If there is already a key at the given time, the key is modified and no 
          * new key is added.
          *
          * \param pTime Time to add the key.
          * \param pKey Key to add.
          * \param pLast Function curve index to speed up search. If this 
          *         function is called in a loop, initialize this value to 0 and 
          *         let it be updated by each call.
          * \return Index of the key at given time, no matter if it was added 
          *         or already present.
          * \remarks Key value, interpolation type and tangent mode must be set 
          *         explicitly afterwards.
          */
        virtual int KeyAdd (KTime pTime, KFbxAnimCurveKeyBase& pKey, int* pLast = NULL) = 0; 
        /** Add a key at given time.
          * \param pTime Time to add the key.
          * \param pLast Function curve index to speed up search. If this 
          *         function is called in a loop, initialize this value to 0 and 
          *         let it be updated by each call.
          */
        virtual int KeyAdd (KTime pTime, int* pLast = NULL) = 0;

        /** Set key at given index.
          * \param pIndex Index of where the key should be set
          * \param pKey the key to set
          * \return \c true if key time is superior to previous key and inferior 
          *         to next key.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual bool KeySet(int pIndex,  KFbxAnimCurveKeyBase& pKey) = 0;
        
        /** Remove key at given index.
          * \param pIndex Index of key to remove.
          * \return true on success.
          */
        virtual bool KeyRemove(int pIndex) = 0;

        /** Insert a key at given time.
          * This function SHOULD be used instead of KFbxAnimCurve::KeyAdd() if the key 
          * is to be added in the curve and not at the end. It inserts the key in 
          * respect to the interpolation type and tangents of the neighboring keys. 
          * If there is already a key a the given time, the key is modified and no 
          * new key is added.
          *
          * \param pTime Time to insert the key.
          * \param pLast Function curve index to speed up search. If this 
          *         function is called in a loop, initialize this value to 0 
          *         and let it be updated by each call.
          * \return Index of the key at given time, no matter if it was inserted 
          *         or already present.
          * \remarks Key value must be set explicitly afterwards. The 
          *         interpolation type and tangent mode are copied from the previous key.
          */
        virtual int KeyInsert ( KTime pTime, int* pLast = NULL ) = 0;
        
        /** Find key index for a given time.
          * \param pTime Time of the key looked for.
          * \param pLast Function curve index to speed up search. If this 
          *         function is called in a loop, initialize this value to 0 
          *         and let it be updated by each call.
          * \return Key index. The integer part of the key index gives the index of 
          *         the closest key with a smaller time. The decimals give the relative 
          *         position of given time compared to previous and next key times. 
          *         Returns -1 if function curve has no key.
          */
        virtual double KeyFind (KTime pTime, int* pLast = NULL) = 0;

        /** Scale value of all keys.
          * \param pMultValue Scale applied on key values.
          * \return \c true on success.
          */
        virtual bool KeyScaleValue (float pMultValue) = 0;

        /** Scale value and tangent of all keys.
          * \param pMultValue Scale applied on key values and tangents.
          * \return \c true on success.
          */
        virtual bool KeyScaleValueAndTangent (float pMultValue) = 0;
    //@}

    /**
    * \name Key Manipulation
    */


     //@{
        /** Set a key.
          * Use SetTCB() to set a key with cubic interpolation and TCB tangent type.
          * \param pKeyIndex            Key index
          * \param pTime                Key time.
          * \param pValue               Key value.
          * \param pInterpolation       Key interpolation type.
          * \param pTangentMode         Key tangent mode (meaningful for cubic interpolation only).
          * \param pData0               Right slope.
          * \param pData1               Next left slope.
          * \param pTangentWeightMode    Weight mode.
          * \param pWeight0             Right slope weight.
          * \param pWeight1             Next left slope weight.
          * \param pVelocity0           Right velocity.
          * \param pVelocity1           Next left velocity.
          */
		virtual void KeySet(int pKeyIndex,KTime pTime, float pValue, KFbxAnimCurveDef::EInterpolationType pInterpolation = KFbxAnimCurveDef::eINTERPOLATION_CUBIC, KFbxAnimCurveDef::ETangentMode pTangentMode = KFbxAnimCurveDef::eTANGENT_AUTO, float pData0 = 0.0,float pData1 = 0.0,KFbxAnimCurveDef::EWeightedMode pTangentWeightMode = KFbxAnimCurveDef::eWEIGHTED_NONE, float pWeight0 = KFbxAnimCurveDef::kDEFAULT_WEIGHT,float pWeight1 = KFbxAnimCurveDef::kDEFAULT_WEIGHT,float pVelocity0 = KFbxAnimCurveDef::kDEFAULT_VELOCITY,float pVelocity1 = KFbxAnimCurveDef::kDEFAULT_VELOCITY) = 0;

        /** Set a key with cubic interpolation, TCB tangent mode.
          * \param pKeyIndex    Key index
          * \param pTime        Key time.
          * \param pValue       Key value.
          * \param pData0       Tension.
          * \param pData1       Continuity.
          * \param pData2       Bias.
          */
        virtual void KeySetTCB(int pKeyIndex,KTime pTime, float pValue, float pData0 = 0.0f, float pData1 = 0.0f, float pData2 = 0.0f) = 0;

        /** Get key interpolation type.
          * \param pKeyIndex       Key index
          * \return                Key interpolation type
          */
        virtual KFbxAnimCurveDef::EInterpolationType KeyGetInterpolation(int pKeyIndex) const = 0;

        /** Set key interpolation type.
          * \param pKeyIndex      Key index
          * \param pInterpolation Key interpolation type.
          */
        virtual void KeySetInterpolation(int pKeyIndex, KFbxAnimCurveDef::EInterpolationType pInterpolation) = 0;

        /** Get key constant mode.
          * Warning: This method is meaningful for constant interpolation only.
          *             Using this method for non constant interpolated key will return unpredicted value.
          * \param pKeyIndex Key index
          * \return Key constant mode.
          */
        virtual KFbxAnimCurveDef::EConstantMode KeyGetConstantMode(int pKeyIndex) const = 0;

        /** Get key tangent mode.
          * \param pKeyIndex  
          * \param pIncludeOverrides
          * Warning: This method is meaningful for cubic interpolation only.
          *             Using this method for non cubic interpolated key will return unpredicted value.
          * \return Key tangent mode.
          */
        virtual KFbxAnimCurveDef::ETangentMode KeyGetTangentMode(int pKeyIndex, bool pIncludeOverrides = false ) const = 0;

        /** Set key constant mode.
          * Warning: This method is meaningful for constant interpolation only.
          * \param pKeyIndex Key index
          * \param pMode Key constant mode.
          */
        virtual void KeySetConstantMode(int pKeyIndex, KFbxAnimCurveDef::EConstantMode pMode) = 0;

        /** Set key tangent mode.
          * Warning: This method is meaningful for cubic interpolation only.
          * \param pKeyIndex  Key index
          * \param pTangent   Key tangent mode.
          */
        virtual void KeySetTangentMode(int pKeyIndex, KFbxAnimCurveDef::ETangentMode pTangent) = 0;

        /** Get key at given index.
          * \param pIndex The index.
          * \return Pointer to the key at the given index.
          * \remarks Result is undetermined if this curve has no key or index is out of bounds.
          */
		virtual KFbxAnimCurveKey KeyGet(int pIndex) const = 0;

        /** Get key value.
          * \param pKeyIndex Key index.
          * \return Value of key.
          */
        virtual float KeyGetValue(int pKeyIndex) const = 0;

        /** Set key value.
          * \param pKeyIndex Key index.
          * \param pValue    The value to set.
          */
        virtual void KeySetValue(int pKeyIndex, float pValue) = 0;

        /** Increment key value.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which key value is incremented.
          */
        virtual void KeyIncValue(int pKeyIndex, float pValue) = 0;

        /** Multiply key value.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which the key value is multiplied.
          */
        virtual void KeyMultValue(int pKeyIndex, float pValue) = 0;

        /** Multiply key tangents.
          * Note: When multiplying a key value, tangents must be
          *       multiplied to conserve the same topology.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which key tangents are multiplied.
          */
        virtual void KeyMultTangent(int pKeyIndex, float pValue) = 0;

        /** Get key time
          * \param pKeyIndex Key index.
          * \return Key time (time at which this key is occurring).
          */
        virtual KTime KeyGetTime(int pKeyIndex) const = 0;

        /** Set key time.
          * \param pKeyIndex Key index.
          * \param pTime     Key time (time at which this key is occurring).
          */
        virtual void KeySetTime(int pKeyIndex, KTime pTime) = 0;

        /** Set/Unset Break tangent
          * Only valid for User and Auto keys.
          * \param pKeyIndex Key index.
          * \param pVal Break flag.
          */
        virtual void KeySetBreak(int pKeyIndex, bool pVal) = 0; 

        /** Get if tangent is break
          * Only valid for User and Auto keys.
          * \param pKeyIndex Key index.
          */
        virtual bool KeyGetBreak(int pKeyIndex) const = 0; 
    //@}

    /**
      * \name Key Tangent Management
      */
    //@{
        /** Get the left derivative of a key.
          * \param pIndex Index of key.
          * \return Left derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual float KeyGetLeftDerivative(int pIndex) = 0;

        /** Set the left derivative of a key.
          * \param pIndex Index of key.
          * \param pValue Left derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *          is out of bounds. This function is only relevant if previous key interpolation
          *          type is eINTERPOLATION_CUBIC and tangent mode is eTANGENT_USER, eTANGENT_BREAK or eTANGENT_AUTO. 
          */
        virtual void KeySetLeftDerivative(int pIndex, float pValue) = 0;

        /** Get the left auto parametric of a key.
          * \param pIndex Index of key.
          * \param pApplyOvershootProtection Clamp is taken into account.
          * \return Left auto parametric.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual float KeyGetLeftAuto(int pIndex, bool pApplyOvershootProtection = false) = 0;

	    /** Get the left derivative info of a key.
		  *	\param pIndex Index of key.
		  *	\return Left derivative.
		  * \remarks Result is undetermined if function curve has no key or index 
		  * is out of bounds.
		  */
		virtual KFCurveTangeantInfo KeyGetLeftDerivativeInfo(int pIndex) = 0;

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
		virtual void KeySetLeftDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false) = 0;

        /** Get the right derivative of a key.
          * \param pIndex Index of key.
          * \return Right derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *          is out of bounds.
          */
        virtual float KeyGetRightDerivative(int pIndex) = 0;

        /** Set the right derivative of a key.
          * \param pIndex Index of key.
          * \param pValue Right derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds. This function is only relevant if previous key interpolation
          *         type is eINTERPOLATION_CUBIC and tangent mode is eTANGENT_USER, eTANGENT_BREAK or eTANGENT_AUTO.
          */
        virtual void KeySetRightDerivative(int pIndex, float pValue) = 0;

        /** Get the right auto parametric of a key.
          * \param pIndex Index of key.
          * \param pApplyOvershootProtection Clamp is taken into account.
          * \return Right auto parametric.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual float KeyGetRightAuto(int pIndex, bool pApplyOvershootProtection = false) = 0;

		/** Get the right derivative info of a key.
		  *	\param pIndex Index of key.
		  *	\return Right derivative info.
		  * \remarks Result is undetermined if function curve has no key or index 
		  * is out of bounds.
		  */
		virtual KFCurveTangeantInfo KeyGetRightDerivativeInfo(int pIndex) = 0;

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
        virtual void KeySetRightDerivativeInfo(kFCurveIndex pIndex, KFCurveTangeantInfo pValue, bool pForceDerivative = false) = 0;

        /** Get the left tangent weight mode of a key.
          * \param pIndex Index of key.
          * \return \c true if the key is weighted.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual bool KeyIsLeftTangentWeighted(int pIndex) const = 0;

        /** Get the right tangent weight mode of a key.
          * \param pIndex Index of key.
          * \return \c true if the key is weighted.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        virtual bool KeyIsRightTangentWeighted(int pIndex) const = 0;

        /** Get the weight value component of the left tangent of a key.
          * \param pIndex Index of key.
          * \return Left tangent weight.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC
          */
        virtual float KeyGetLeftTangentWeight(int pIndex) const = 0;

        /** Get the weight value component of the right tangent of a key.
          * \param pIndex Index of key.
          * \return Right tangent weight.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC
          */
        virtual float KeyGetRightTangentWeight(int pIndex) const = 0;

        /** Set the left tangent weight of a key.
          * \param pIndex Index of key.
          * \param pWeight Weight value.
          * \param pAdjustTan When set to \c true, recompute the tangent height to compensate for very small weights. 
          * \remarks This function is only relevant if previous key interpolation type is eINTERPOLATION_CUBIC and 
          *         tangent mode is eTANGENT_USER or eTANGENT_BREAK. The tangent is automatically set in weighted mode.
          * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
          *         set before calling this function.
          */
        virtual void   KeySetLeftTangentWeight( int pIndex, float pWeight, bool pAdjustTan = false ) = 0;

        /** Set the right tangent weight of a key.
          * \param pIndex Index of key.
          * \param pWeight Weight value.
          * \param pAdjustTan When set to \c true, recompute the tangent height to compensate for very small weights.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC and tangent 
          *         mode is eTANGENT_USER or eTANGENT_BREAK. The tangent is automatically set in weighted mode.
          * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
          *         set before calling this function.
          */
        virtual void   KeySetRightTangentWeight( int pIndex, float pWeight, bool pAdjustTan = false  ) = 0;

        /** Get the velocity value component of the left tangent of a key
          *	\param pIndex Index of key.
          *	\return Left tangent velocity.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC.
          */
        virtual float KeyGetLeftTangentVelocity( int pIndex) const = 0;

        /** Get the velocity value component of the right tangent of a key
          *	\param pIndex Index of key.
          *	\return Right tangent velocity.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC.
          */		
        virtual float KeyGetRightTangentVelocity( int pIndex) const = 0;

    //@}

    /**
      * \name Evaluation and Analysis
      */
    //@{
        /** Evaluate function curve value at a given time.
          * \param pTime Time of evaluation.
          *              If time falls between two keys, function curve value is 
          *              interpolated according to previous key interpolation type and
          *              tangent mode if relevant.
          * \param pLast Index of the last processed key. If this 
          *              function is called in a loop, initialize this value to 0 and let it 
          *              be updated by each call.
          * \return Evaluated curve value.
          * \remarks This function takes extrapolation into account.
          */
          virtual float Evaluate (KTime pTime, int* pLast = NULL) = 0;

        /** Evaluate function curve value at the given key index.
          * \param pIndex Any value between 0 and KFbxAnimCurve::KeyGetCount() - 1.
          *               If this index falls between keys, the function curve value is 
          *               interpolated according to previous key interpolation type and
          *               tangent mode if relevant.
          * \return Evaluated curve value.
          * \remarks This function does not take extrapolation into account.
          */
        virtual float EvaluateIndex( double pIndex) = 0;
        
        /** Evaluate function left derivative at given time.
          * \param pTime Time of evaluation.
          * \param pLast Function curve index to speed up search. If this 
          *              function is called in a loop, initialize this value to 0 and let it 
          *              be updated by each call.
          * \return Left derivative at given time.
          * \remarks This function does not take extrapolation into account.
          */
          virtual float EvaluateLeftDerivative (KTime pTime, int* pLast = NULL) = 0;
        
        /** Evaluate function right derivative at given time.
          * \param pTime Time of evaluation.
          * \param pLast Function curve index to speed up search. If this 
          *              function is called in a loop, initialize this value to 0 and let it 
          *              be updated by each call.
          * \return Right derivative at given time.
          * \remarks This function does not take extrapolation into account.
          */
          virtual float EvaluateRightDerivative (KTime pTime, int* pLast = NULL) = 0;
    //@}

    /**
      * \name Utility functions.
      *
      */
    //@{
        /** Find out start and end time of the animation curve.
          * This function retrieves the Curve's time span.
          * \param pStart Reference to receive start time.
          * \param pStop Reference to receive end time.
          * \return \c true on success, \c false otherwise.
          */
        virtual bool GetTimeInterval(KTime& pStart, KTime& pStop) = 0;

        /** Returns the pointer to KFCurve.
          * \return Pointer to KFCurve.
		  * \remarks Subject to be deprecated (2009-2010)
          */
        virtual KFCurve* GetKFCurve() = 0;

		/** Copy curve content into current curve.
          * \param pSource Source curve.
          * \param pWithKeys If \c true, clear keys in current function curve and copy
          * keys from source function curve. If \c false, keys in current function curve
          * are left as is.
        */
        virtual void CopyFrom(KFbxAnimCurve& pSource, bool pWithKeys = true) = 0;
    //@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    ///////////////////////////////////////////////////////////////////////////////
    //  WARNING!
    //    Anything beyond these lines may not be documented accurately and is 
    //     subject to change without notice.
    ///////////////////////////////////////////////////////////////////////////////

	virtual bool Store(KFbx* pFileObject) = 0;
    virtual bool Retrieve(KFbx* pFileObject) = 0;

protected:
    KFbxAnimCurve(KFbxSdkManager& pManager, char const* pName);

	virtual void Construct(const KFbxAnimCurveBase* pFrom);
	virtual void Destruct(bool pRecursive, bool pDependents);

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif // FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVE_H
