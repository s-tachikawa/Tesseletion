/*!  \file kfbxanimcurvekfcurve.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVEKFCURVE_H
#define FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVEKFCURVE_H

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
#include <fbxfilesdk/kfbxplugins/kfbxanimcurve.h>
#include <fbxfilesdk/kfbxplugins/kfbxobject.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

static void CollectAnimFromCurveNode(KFCurve **lSrc, KFCurveNode *fcn, unsigned int nbCrvs, KFbxAnimCurveNode *cn);

/** This is the base class implementing the Fbx animation function curves keys.
  * \nosubgrouping
  * This class, for the time being, encapsulates the old KFCurveKey
  * structure. However, in a near future, this will become the
  * main animation curve key object of the SDK and the implementation
  * is subject to change.
  */
class KFBX_DLL KFbxAnimCurveKFCurveKey : public KFbxAnimCurveKeyImpl
{
private:
    KFCurveKey mKey;

public:
	static KFbxAnimCurveKeyImpl* AllocatorFct()
	{
		return FbxSdkNew<KFbxAnimCurveKFCurveKey>();
	}

	static KFbxAnimCurveKeyImpl* CopyAllocatorFct(KFbxAnimCurveKeyImpl* pImpl)
	{
		return FbxSdkNew<KFbxAnimCurveKFCurveKey>(*((KFbxAnimCurveKFCurveKey*)pImpl));
	}

	static void DeallocatorFct(KFbxAnimCurveKeyImpl* pImpl)
	{
		FbxSdkDelete<KFbxAnimCurveKFCurveKey>((KFbxAnimCurveKFCurveKey*)pImpl);
	}

    /** Default Constructor.
    */
	KFbxAnimCurveKFCurveKey() : KFbxAnimCurveKeyImpl()
    {
		KTime lTime = GetTime();
		SetTime(lTime);
        mKey.Set(lTime, 0.0);
    };

    /** Destructor.
    */
    virtual ~KFbxAnimCurveKFCurveKey()
    {
        // nothing specific to do!
    }

	KFbxAnimCurveKFCurveKey(KTime pTime) : KFbxAnimCurveKeyImpl()
	{
		SetTime(pTime);
		mKey.Set(pTime, 0.0);
	}

	KFbxAnimCurveKFCurveKey(KTime pTime, float pVal) : KFbxAnimCurveKeyImpl()
	{
		SetTime(pTime);
		mKey.Set(pTime, pVal);

	}

	/** Copy constructor.
      * \param pFKey KFbxAnimCurveKFCurveKey instance to be copied.
      */
    KFbxAnimCurveKFCurveKey(KFbxAnimCurveKFCurveKey const& pFKey) : KFbxAnimCurveKeyImpl()
    {
		mKey = pFKey.mKey;
        SetTime(mKey.GetTime());
    };

    /** Constructor from KFCurveKey.
      * \param pFKey KFCurveKey instance to be copied.
      */
    KFbxAnimCurveKFCurveKey(KFCurveKey const& pFKey) : KFbxAnimCurveKeyImpl()
    {
        mKey = pFKey;
        SetTime(mKey.GetTime());
    };

	/** Assignment operator.
	  */
    KFbxAnimCurveKeyImpl& operator=(const KFbxAnimCurveKeyImpl& pFKey)
	{
		*this = *((KFbxAnimCurveKFCurveKey*)&pFKey);
		return *this;
	}

	/** Assignment operator.
	  */
	KFbxAnimCurveKFCurveKey& operator=(const KFbxAnimCurveKFCurveKey& pFKey)
	{
		SetTime(pFKey.GetTime());
		mKey = pFKey.mKey;
		return *this;
	}

    /** Operator to convert this to its base class instance.
      */
    operator KFCurveKey&()
    { 
        return mKey; 
    };

    /** Get base class pointer.
      * \return Base class pointer.
      */
    KFCurveKey* GetKFCurveKey()
    {
        return &mKey;
    };

    /** Get time value.
    * \return Time value.
    */
    virtual KTime GetTime() const
    {
        return mKey.GetTime();
    };

    /** Set time of key.
      * \param pTime New time of this key.
      */
    virtual void  SetTime(const KTime& pTime)
    {
        mKey.SetTime(pTime);
    };

    /** Set time and value of key.
      * \param pTime New time of this key.
      * \param pValue New value of this key.
      */
    void Set(KTime pTime, float pValue)
    {
        mKey.Set(pTime, pValue);
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
		mKey.SetTCB(pTime, pValue, pData0, pData1, pData2);
	}

    /** Get key value.
    *	\return Key value.
    */
    float GetValue() const
	{
		return mKey.GetValue();
	}

	/** Set key value.
	  * \param pValue Key value to set.
	  */
	void SetValue(float pValue)
	{
		mKey.SetValue(pValue);
	}

	/** Get key interpolation.
    *	\return Key interpolation.
    */
    KFbxAnimCurveDef::EInterpolationType GetInterpolation() const
	{
		return KFbxAnimCurveDef::EInterpolationType(mKey.GetInterpolation());
	}

	/** Set key interpolation.
	  * \param pInterpolation Interpolation type to set.
	  */
	void SetInterpolation (KFbxAnimCurveDef::EInterpolationType pInterpolation)
	{
		mKey.SetInterpolation(pInterpolation);
	}

	/** Get tangent mode.
    *	\return Tangent mode.
    */
    KFbxAnimCurveDef::ETangentMode GetTangentMode(bool pIncludeOverrides = false) const
	{
		return KFbxAnimCurveDef::ETangentMode(mKey.GetTangeantMode(pIncludeOverrides));
	}

	/** Set tangent mode.
	  * \param pTangentMode Tangent mode to set.
	  */
	void SetTangentMode (KFbxAnimCurveDef::ETangentMode pTangentMode)
	{
        bool lTI = (pTangentMode&KFbxAnimCurveDef::eTANGENT_GENERIC_TIME_INDEPENDENT)==KFbxAnimCurveDef::eTANGENT_GENERIC_TIME_INDEPENDENT;
		mKey.SetTangeantMode(pTangentMode, lTI==false);
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
		return KFbxAnimCurveDef::EWeightedMode(mKey.GetTangeantWeightMode());
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
		mKey.SetTangeantWeightMode(pTangentWeightMode, pMask);
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
		return KFbxAnimCurveDef::EVelocityMode(mKey.GetTangeantVelocityMode());
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
		mKey.SetTangeantVelocityMode(pTangentVelocityMode, pMask);
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
		return KFbxAnimCurveDef::EConstantMode(mKey.GetConstantMode());
	}

	/** Set constant mode.
	  * \param pMode Constant mode to set.
	  */
	void SetConstantMode(KFbxAnimCurveDef::EConstantMode pMode)
	{
		mKey.SetConstantMode(pMode);
	}

	/** Get data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \return Data value.
	  */
	float GetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex) const
	{
		// VR: The way KFCurveKey::GetDataFloat() and GetDataDouble() are implemented are different.
		// GetDataDouble() works for cases USER, AUTO, BREAK, etc, which have 2 or 4 float values to store.
		// GetDataFloat() works for the TCB case which has 3 float values (Tension, Continuity and Bias).
		// It is not my purpose to modivy KFCurveKey at this point, so we use GetDataDouble in general,
		// and GetDataFloat in the case of a TCB.

		if (GetTangentMode() == KFbxAnimCurveDef::eTANGENT_TCB)
		{
			return mKey.GetDataFloat(EKFCurveDataIndex(pIndex));
		}

		return (float)mKey.GetDataDouble(EKFCurveDataIndex(pIndex));
	}

	/** Set data float
	  * \param pIndex Data index, dependent on the key tangent mode.
	  * \param pValue Data value to set.
	  */
	void SetDataFloat(KFbxAnimCurveDef::EKFbxAnimCurveDataIndex pIndex, float pValue)
	{
		// VR: The way KFCurveKey::SetDataFloat() and SetDataDouble() are implemented are different.
		// SetDataDouble() works for cases USER, AUTO, BREAK, etc, which have 2 or 4 float values to store.
		// SetDataFloat() works for the TCB case which has 3 float values (Tension, Continuity and Bias).
		// It is not my purpose to modivy KFCurveKey at this point, so we use SetDataDouble in general,
		// and SetDataFloat in the case of a TCB.

		if (GetTangentMode() == KFbxAnimCurveDef::eTANGENT_TCB)
		{
			mKey.SetDataFloat(EKFCurveDataIndex(pIndex), pValue);
		}

		mKey.SetDataDouble(EKFCurveDataIndex(pIndex), (kFCurveDouble)pValue);
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
		mKey.SetTangeantVisibility(pVisibility);
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
		return KFbxAnimCurveDef::ETangentVisibility(mKey.GetTangeantVisibility());
	}

	/** Set/Unset Break tangent
	* Only valid for User and Auto keys
	* \param pVal The break flag.
	*/
	void SetBreak(bool pVal)
	{
		mKey.SetBreak(pVal);
	}

	/** Get if tangent is break
	* Only valid for User and Auto keys
	*/
	bool GetBreak() const
	{
		return mKey.GetBreak();
	}
};


/** This is the base class implementing the Fbx animation function curves.
  * \nosubgrouping
  * This class, for the time being, encapsulates the old KFCurve
  * structure. However, in a near future, this will become the
  * main animation curve object of the SDK and the implementation
  * is subject to change.
  */
class KFBX_DLL KFbxAnimCurveKFCurve : public KFbxAnimCurve
{
    KFBXOBJECT_DECLARE(KFbxAnimCurveKFCurve, KFbxAnimCurve);

public:

	/** Get default value.
	  * Default value is used when there is no key in the function curve.
	  *	\return Default value.
	  */
	float GetValue() const;

    /**
      * \name Key management.
      *
      */
    //@{
        /** Resize curve buffer to hold a certain number of key.
          * \param pKeyCount Number of key the curve will eventually hold.
          */
        void ResizeKeyBuffer(int pKeyCount);

        /** Call this function prior to modifying the keys of this curve.
          * \remarks Be sure to call KFbxAnimCurve::KeyModifyEnd() after modification 
          *         of the keys are completed.
          */
        void KeyModifyBegin ();
        
        /** Call this function after modification of the keys of this curve.
          * \remarks You need to call KFCurve::KeyModifyBegin() prior to modifying 
          *         the keys.
          */
        void KeyModifyEnd ();

        //! Minimize use of buffer memory.
        void KeyShrink();

        //! Remove all the keys and free buffer memory.
        virtual void KeyClear (); 
       
        /** Get the number of keys.
          * \return Key count.
          */
        virtual int KeyGetCount () const;
  
        /** Add a key at given time.
          * Function KFbxAnimCurveFCurve::KeyInsert() SHOULD be used instead if the key 
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
        int KeyAdd (KTime pTime, KFbxAnimCurveKeyBase& pKey, int* pLast = NULL); 
        /** Add a key at given time.
          * \param pTime Time to add the key.
          * \param pLast Function curve index to speed up search. If this 
          *         function is called in a loop, initialize this value to 0 and 
          *         let it be updated by each call.
          */
        int KeyAdd (KTime pTime, int* pLast = NULL) 
        {   
            KFbxAnimCurveKFCurveKey key(pTime);
            return KeyAdd(pTime, key, pLast); 
        }

        /** Set key at given index.
          * \param pIndex Index of where the key should be set
          * \param pKey the key to set
          * \return \c true if key time is superior to previous key and inferior 
          *         to next key.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        bool KeySet(int pIndex,  KFbxAnimCurveKeyBase& pKey);
        
        /** Remove key at given index.
          * \param pIndex Index of key to remove.
          * \return true on success.
          */
        bool KeyRemove(int pIndex);

        /** Insert a key at given time.
          * This function SHOULD be used instead of KFbxAnimCurveFCurve::KeyAdd() if the key 
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
        int KeyInsert ( KTime pTime, int* pLast = NULL );
        
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
        double KeyFind (KTime pTime, int* pLast = NULL);

        /** Scale value of all keys.
          * \param pMultValue Scale applied on key values.
          * \return \c true on success.
          */
        bool KeyScaleValue (float pMultValue);

        /** Scale value and tangent of all keys.
          * \param pMultValue Scale applied on key values and tangents.
          * \return \c true on success.
          */
        bool KeyScaleValueAndTangent (float pMultValue);
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
        void KeySet 
        (
            int pKeyIndex,
            KTime pTime, 
            float pValue, 
            KFbxAnimCurveDef::EInterpolationType pInterpolation = KFbxAnimCurveDef::eINTERPOLATION_CUBIC, 
            KFbxAnimCurveDef::ETangentMode pTangentMode = KFbxAnimCurveDef::eTANGENT_AUTO, 
            float pData0 = 0.0,
            float pData1 = 0.0,
            KFbxAnimCurveDef::EWeightedMode pTangentWeightMode = KFbxAnimCurveDef::eWEIGHTED_NONE, 
            float pWeight0 = KFbxAnimCurveDef::kDEFAULT_WEIGHT,
            float pWeight1 = KFbxAnimCurveDef::kDEFAULT_WEIGHT,
            float pVelocity0 = KFbxAnimCurveDef::kDEFAULT_VELOCITY,
            float pVelocity1 = KFbxAnimCurveDef::kDEFAULT_VELOCITY
        );

        /** Set a key with cubic interpolation, TCB tangent mode.
          * \param pKeyIndex    Key index
          * \param pTime        Key time.
          * \param pValue       Key value.
          * \param pData0       Tension.
          * \param pData1       Continuity.
          * \param pData2       Bias.
          */
        void KeySetTCB 
        (
            int pKeyIndex,
            KTime pTime, 
            float pValue, 
            float pData0 = 0.0f, 
            float pData1 = 0.0f, 
            float pData2 = 0.0f
        );

        /** Get key interpolation type.
          * \param pKeyIndex       Key index
          * \return                Key interpolation type
          */
        KFbxAnimCurveDef::EInterpolationType KeyGetInterpolation(int pKeyIndex) const;

        /** Set key interpolation type.
          * \param pKeyIndex      Key index
          * \param pInterpolation Key interpolation type.
          */
        void KeySetInterpolation(int pKeyIndex, KFbxAnimCurveDef::EInterpolationType pInterpolation);

        /** Get key constant mode.
          * Warning: This method is meaningful for constant interpolation only.
          *             Using this method for non constant interpolated key will return unpredicted value.
          * \param pKeyIndex Key index
          * \return Key constant mode.
          */
        KFbxAnimCurveDef::EConstantMode KeyGetConstantMode(int pKeyIndex) const;

        /** Get key tangent mode.
          * \param pKeyIndex  
          * \param pIncludeOverrides
          * Warning: This method is meaningful for cubic interpolation only.
          *             Using this method for non cubic interpolated key will return unpredicted value.
          * \return Key tangent mode.
          */
        KFbxAnimCurveDef::ETangentMode KeyGetTangentMode(int pKeyIndex, bool pIncludeOverrides = false ) const;

        /** Set key constant mode.
          * Warning: This method is meaningful for constant interpolation only.
          * \param pKeyIndex Key index
          * \param pMode Key constant mode.
          */
        void KeySetConstantMode(int pKeyIndex, KFbxAnimCurveDef::EConstantMode pMode);

        /** Set key tangent mode.
          * Warning: This method is meaningful for cubic interpolation only.
          * \param pKeyIndex  Key index
          * \param pTangent   Key tangent mode.
          */
        void KeySetTangentMode(int pKeyIndex, KFbxAnimCurveDef::ETangentMode pTangent);

        /** Get key at given index.
          * \param pIndex The index.
          * \return A copy of the key at the given index.
          * \remarks Result is undetermined if this curve has no key or index is out of bounds.
          */
        KFbxAnimCurveKey KeyGet(int pIndex) const;

        /** Get key value.
          * \param pKeyIndex Key index.
          * \return Value of key.
          */
        float KeyGetValue(int pKeyIndex) const;

        /** Set key value.
          * \param pKeyIndex Key index.
          * \param pValue    The value to set.
          */
        void KeySetValue(int pKeyIndex, float pValue);

        /** Increment key value.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which key value is incremented.
          */
        void KeyIncValue(int pKeyIndex, float pValue);

        /** Multiply key value.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which the key value is multiplied.
          */
        void KeyMultValue(int pKeyIndex, float pValue);

        /** Multiply key tangents.
          * Note: When multiplying a key value, tangents must be
          *       multiplied to conserve the same topology.
          * \param pKeyIndex Key index.
          * \param pValue    Value by which key tangents are multiplied.
          */
        void KeyMultTangent(int pKeyIndex, float pValue);

        /** Get key time
          * \param pKeyIndex Key index.
          * \return Key time (time at which this key is occurring).
          */
        virtual KTime KeyGetTime(int pKeyIndex) const;

        /** Set key time.
          * \param pKeyIndex Key index.
          * \param pTime     Key time (time at which this key is occurring).
          */
        virtual void KeySetTime(int pKeyIndex, KTime pTime);

        /** Set/Unset Break tangent
          * Only valid for User and Auto keys.
          * \param pKeyIndex Key index.
          * \param pVal Break flag.
          */
        void KeySetBreak(int pKeyIndex, bool pVal); 

        /** Get if tangent is break
          * Only valid for User and Auto keys.
          * \param pKeyIndex Key index.
          */
        bool KeyGetBreak(int pKeyIndex) const; 
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
        float KeyGetLeftDerivative(int pIndex);

        /** Set the left derivative of a key.
          * \param pIndex Index of key.
          * \param pValue Left derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *          is out of bounds. This function is only relevant if previous key interpolation
          *          type is eINTERPOLATION_CUBIC and tangent mode is eTANGENT_USER, eTANGENT_BREAK or eTANGENT_AUTO. 
          */
        void KeySetLeftDerivative(int pIndex, float pValue);

        /** Get the left auto parametric of a key.
          * \param pIndex Index of key.
          * \param pApplyOvershootProtection Clamp is taken into account.
          * \return Left auto parametric.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        float KeyGetLeftAuto(int pIndex, bool pApplyOvershootProtection = false);

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

        /** Get the right derivative of a key.
          * \param pIndex Index of key.
          * \return Right derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *          is out of bounds.
          */
        float KeyGetRightDerivative(int pIndex);

        /** Set the right derivative of a key.
          * \param pIndex Index of key.
          * \param pValue Right derivative.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds. This function is only relevant if previous key interpolation
          *         type is eINTERPOLATION_CUBIC and tangent mode is eTANGENT_USER, eTANGENT_BREAK or eTANGENT_AUTO.
          */
        void KeySetRightDerivative(int pIndex, float pValue);

        /** Get the right auto parametric of a key.
          * \param pIndex Index of key.
          * \param pApplyOvershootProtection Clamp is taken into account.
          * \return Right auto parametric.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        float KeyGetRightAuto(int pIndex, bool pApplyOvershootProtection = false);

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

        /** Get the left tangent weight mode of a key.
          * \param pIndex Index of key.
          * \return \c true if the key is weighted.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        bool KeyIsLeftTangentWeighted(int pIndex) const;

        /** Get the right tangent weight mode of a key.
          * \param pIndex Index of key.
          * \return \c true if the key is weighted.
          * \remarks Result is undetermined if function curve has no key or index 
          *         is out of bounds.
          */
        bool KeyIsRightTangentWeighted(int pIndex) const;

        /** Get the weight value component of the left tangent of a key.
          * \param pIndex Index of key.
          * \return Left tangent weight.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC
          */
        float KeyGetLeftTangentWeight(int pIndex) const;

        /** Get the weight value component of the right tangent of a key.
          * \param pIndex Index of key.
          * \return Right tangent weight.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC
          */
        float KeyGetRightTangentWeight(int pIndex) const;

        /** Set the left tangent weight of a key.
          * \param pIndex Index of key.
          * \param pWeight Weight value.
          * \param pAdjustTan When set to \c true, recompute the tangent height to compensate for very small weights. 
          * \remarks This function is only relevant if previous key interpolation type is eINTERPOLATION_CUBIC and 
          *         tangent mode is eTANGENT_USER or eTANGENT_BREAK. The tangent is automatically set in weighted mode.
          * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
          *         set before calling this function.
          */
        void   KeySetLeftTangentWeight( int pIndex, float pWeight, bool pAdjustTan = false );

        /** Set the right tangent weight of a key.
          * \param pIndex Index of key.
          * \param pWeight Weight value.
          * \param pAdjustTan When set to \c true, recompute the tangent height to compensate for very small weights.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC and tangent 
          *         mode is eTANGENT_USER or eTANGENT_BREAK. The tangent is automatically set in weighted mode.
          * \remarks The pAdjustTan option will only produce correct results provided that the tangent has already been
          *         set before calling this function.
          */
        void   KeySetRightTangentWeight( int pIndex, float pWeight, bool pAdjustTan = false  );

        /** Get the velocity value component of the left tangent of a key
          *	\param pIndex Index of key.
          *	\return Left tangent velocity.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC.
          */
        float KeyGetLeftTangentVelocity( int pIndex) const;

        /** Get the velocity value component of the right tangent of a key
          *	\param pIndex Index of key.
          *	\return Right tangent velocity.
          * \remarks This function is only relevant if key interpolation type is eINTERPOLATION_CUBIC.
          */		
        float KeyGetRightTangentVelocity( int pIndex) const;

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
          virtual float Evaluate (KTime pTime, int* pLast = NULL);

        /** Evaluate function curve value at the given key index.
          * \param pIndex Any value between 0 and KFCurve::KeyGetCount() - 1.
          *               If this index falls between keys, the function curve value is 
          *               interpolated according to previous key interpolation type and
          *               tangent mode if relevant.
          * \return Evaluated curve value.
          * \remarks This function does not take extrapolation into account.
          */
        virtual float EvaluateIndex( double pIndex);
        
        /** Evaluate function left derivative at given time.
          * \param pTime Time of evaluation.
          * \param pLast Function curve index to speed up search. If this 
          *              function is called in a loop, initialize this value to 0 and let it 
          *              be updated by each call.
          * \return Left derivative at given time.
          * \remarks This function does not take extrapolation into account.
          */
          float EvaluateLeftDerivative (KTime pTime, int* pLast = NULL);
        
        /** Evaluate function right derivative at given time.
          * \param pTime Time of evaluation.
          * \param pLast Function curve index to speed up search. If this 
          *              function is called in a loop, initialize this value to 0 and let it 
          *              be updated by each call.
          * \return Right derivative at given time.
          * \remarks This function does not take extrapolation into account.
          */
          float EvaluateRightDerivative (KTime pTime, int* pLast = NULL);
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
        virtual bool GetTimeInterval(KTime& pStart, KTime& pStop);

        /** Set the display color of the KFCurve.
          * \param pColor The Desired color.
          */
        void SetColor(float *pColor);

        /** Get the display color of the KFCurve.
          * \return the pointer to the color or NULL.
          */
        float* GetColor();

        /** Returns the pointer to KFCurve.
          * \return Pointer to KFCurve.
          */
        KFCurve* GetKFCurve();

		/** Copy curve content into current curve.
          * \param pSource Source curve.
          * \param pWithKeys If \c true, clear keys in current function curve and copy
          * keys from source function curve. If \c false, keys in current function curve
          * are left as is.
        */
		void CopyFrom(KFbxAnimCurve& pSource, bool pWithKeys = true);
    //@}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    ///////////////////////////////////////////////////////////////////////////////
    //  WARNING!
    //    Anything beyond these lines may not be documented accurately and is 
    //     subject to change without notice.
    ///////////////////////////////////////////////////////////////////////////////
    virtual int KeyAdd (KTime pTime, KFbxAnimCurveKFCurveKey& pKey, int* pLast = 0);
    virtual bool KeySet(int pIndex, KFbxAnimCurveKFCurveKey& pKey);

protected:
    KFbxAnimCurveKFCurve(KFbxSdkManager& pManager, char const* pName);

    virtual void Construct(const KFbxAnimCurve* pFrom);
    virtual void Destruct(bool pRecursive, bool pDependents);
 
	friend void CollectAnimFromCurveNode(KFCurve **lSrc, KFCurveNode *fcn, unsigned int nbCrvs, KFbxAnimCurveNode *cn);
	void SetKFCurve(KFCurve *lKFCurve);
    KFCurve* mFCurve;

public:
    virtual bool Store(KFbx* pFileObject);
    virtual bool Retrieve(KFbx* pFileObject);

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
};

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif // FBXFILESDK_KFBXPLUGINS_KFBXANIMCURVEKFCURVE_H
