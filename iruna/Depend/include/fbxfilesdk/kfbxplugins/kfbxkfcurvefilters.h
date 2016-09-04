/*!  \file kfbxkfcurvefilters.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXKFCURVEFILTERS_H
#define FBXFILESDK_KFBXPLUGINS_KFBXKFCURVEFILTERS_H

/**************************************************************************************

 Copyright (C) 2001 - 2009 Autodesk, Inc. and/or its licensors.
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

#include <fbxfilesdk/kfbxplugins/kfbxobject.h>
#include <fbxfilesdk/components/kbaselib/klib/ktime.h>
#include <fbxfilesdk/components/kbaselib/klib/kerror.h>
#include <fbxfilesdk/kfbxmath/kfbxxmatrix.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

class KFbxAnimStack;
class KFbxAnimCurve;
class KFbxAnimCurveNode;
class KFCurve;
class KFCurveNode;
class KFCurveFilterKeyReducer;
class KFCurveFilterConstantKeyReducer;
class KFCurveFilterMatrixConverter;
class KFCurveFilterResample;
class KFCurveFilterUnroll;
class KFCurveFilterGimbleKiller;
class KFCurveFilterTimeShiftAndScale;
class KFCurveFilterKeySync;
class KFCurveFilterScale;


/** \brief Base class for KFCurveNode and KFCurve filtering.
* \nosubgrouping
* A class is necessary to hold the parameters of a filtering
* algorithm.  Independent UI can then be attached to those
* parameters.
*/
class KFBX_DLL KFbxKFCurveFilter : public KFbxObject
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilter,KFbxObject);

public:
    /** Get the Name of the Filter.
    * \return     Pointer to name.
    */
    virtual const char* GetName() const {return NULL;}

    /** Get the Start Time.
    * \return     The time expressed as KTime.
    */
    virtual KTime& GetStartTime() {return mTime;}

    /** Set the Start Time.
    * \param pTime     The time to be set.
    */
    virtual void SetStartTime(KTime& pTime){return;}

    /** Get the Stop Time.
    * \return     The time expressed as KTime.
    */
    virtual KTime& GetStopTime(){return mTime;}

    /** Set the Stop Time.
    * \param pTime     The time to be set.
    */
    virtual void SetStopTime(KTime& pTime){return ;}

    /** Get the Start Key.
    * \param pCurve     Curve on which we want to retrieve the start key.
    * \return           The position of the start key.
    */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const {return 0;}

    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    virtual int GetStartKey(KFCurve& pCurve) const {return 0;}

    /** Get the Stop Key.
    * \param pCurve     Curve on which we want to retrieve the stop key.
    * \return           The position of the stop key.
    */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const {return 0;}

    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    virtual int GetStopKey(KFCurve& pCurve) const {return 0;}

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack);

    /** Check if all the animated properties of the object need an application of the filter.
    * \param pObj           Object containing the properties to test.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxObject* pObj, KFbxAnimStack* pAnimStack);

    /** Check if the KFbxAnimCurveNode need an application of the filter.
    * \param pCurveNode     Curve to test if it needs application of filter.
    * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode) {return false;}

    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ....)
    * \param pCurveNode
    * \param pRecursive
    */
    virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true){return false;}

    /** Check if the given KFbxAnimCurve need an application of the filter.
    * \param pCurve     Array of Curves to test if they need the and application of the filter.
    * \param pCount     Number of Curves in array.
    * \return           \c true if one or more KFbxAnimCurve in the array need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount){return false;}

    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ....)
    * \param pCurve
    * \param pCount
    */
    virtual bool NeedApply(KFCurve** pCurve, int pCount){return false;}

    /** Check if a KFbxAnimCurve need an application of the filter.
    * \param pCurve     Curve to test if it needs application of filter.
    * \return           \c true if the KFbxAnimCurve need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimCurve& pCurve){return false;}

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack);

    /** Apply filter to all the animated properties of the object.
    * \param pObj           Object containing the properties to apply the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxObject* pObj, KFbxAnimStack* pAnimStack);

    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ....)
    * \param pCurve
    */
    virtual bool NeedApply(KFCurve& pCurve){return false;}

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
    * \param pCurveNode     Curve to apply the filter.
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode){return false;}

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ....)
    * \param pCurveNode
    * \param pRecursive
    */
    virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true){return false;}

    /** Apply filter on a number of KFbxAnimCurve.
    * \param pCurve     Array of curves to apply the filter.
    * \param pCount     Number of curves in array to apply the filter.
    * \return           \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount){return false;}

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ....)
    * \param pCurve
    * \param pCount
    */
    virtual bool Apply(KFCurve** pCurve, int pCount){return false;}

    /** Apply filter on a KFbxAnimCurve.
    * \param pCurve         Curve to apply the filter.
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimCurve& pCurve){return false;}

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ....)
    * \param pCurve
    */
    virtual bool Apply(KFCurve& pCurve){return false;}

    /** Reset default parameters.
    */
    virtual void Reset(){return ;}

    /** Retrieve error object.
    * \return     Error object.
    */
    virtual KError* GetError() {return NULL;}

    /** Get last error ID.
    * \return     Last error ID.
    */
    virtual int GetLastErrorID(){return -1;}

    /** Get last error name.
    * \return     Last error name.
    */
    virtual char* GetLastErrorString(){return NULL;}
///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS

protected:
    KFbxKFCurveFilter(KFbxSdkManager& pManager, char const* pName);
    void GetKFCurvesFromAnimCurve(KFbxAnimCurve** pSrc, int pSrcCount, KFCurve** pDst, int& pDstCount);

    KTime mTime;
#endif
};


/** \brief Key reducing filter.
  * \nosubgrouping
  * Filter to test if each key is really necessary to define the curve
  * at a definite degree of precision. It filters recursively from the
  * strongest difference first. All useless keys are eliminated.
  */
class KFBX_DLL KFbxKFCurveFilterKeyReducer : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterKeyReducer,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

	//!	Get precision.
	double GetPrecision() const;

	/**	Set precision.
	  * \param pPrecision The precision to set.
	  */
	void SetPrecision(double pPrecision);

	//!	Return \c true key sync is applied at the end.
	bool GetKeySync() const;

	/**	Set to \c true to apply key sync at the end.
	  * \param pKeySync Key sync flag.
	  */
	void SetKeySync(bool pKeySync);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterKeyReducer(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterKeyReducer *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);

#endif
};



/** \brief Constant Key reducing filter.
  * \nosubgrouping
  * Filter to test if each key is really necessary to define the curve
  * at a definite degree of precision. It filters recursively from the
  * strongest difference first. All useless keys are eliminated.
  */
class KFBX_DLL KFbxKFCurveFilterConstantKeyReducer : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterConstantKeyReducer,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */    
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** Get the derivative tolerance.
      * \return     The value of the derivative tolerance.
      */
    double GetDerivativeTolerance() const;

    /** Set the derivative tolerance.
      * \param pValue     Value derivative tolerance.
      */
    void SetDerivativeTolerance(double pValue);

    /** Get the tolerance value.
      * \return     The tolerance value.
      */
    double GetValueTolerance() const;

    /** Set the tolerance value.
      * \param pValue     Tolerance value.
      */
    void SetValueTolerance(double pValue);

    /** Get the state of the KeepFirstAndLastKeys flag.
      * \return      \c true if the filter keeps the first and last keys.
      */
    bool GetKeepFirstAndLastKeys() const;

    /** Set the state of the KeepFirstAndLastKeys flag.
      * \param pKeepFirstAndLastKeys     Set to \c true if you want the filter to keep the first and last keys.
      */
    void SetKeepFirstAndLastKeys( bool pKeepFirstAndLastKeys );

    /** Get the state of the KeepOneKey flag.
      * \return     \c true if the filter keeps one keys.
      */
    bool GetKeepOneKey() const;

    /** Set the state of the KeepOneKey flag.
      * \param pKeepOneKey     Set to \c true if you want the filter to keep one key.
      */
    void SetKeepOneKey( bool pKeepOneKey );

    /** Tell the filter keep cubic curve keys which are not pure auto
	  * \param pKeep KeepNotPureAutoKeys flag.
	  */
	void SetKeepNotPureAutoKeys(bool pKeep);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //
    //  If ValueTolerance is default, we use the thresholds here, otherwise
    //  it is the ValueTolerance that is used. (Mainly for backward compatibility)
    //
    void SetTranslationThreshold    ( double pTranslationThreshold );
    void SetRotationThreshold       ( double pRotationThreshold );
    void SetScalingThreshold        ( double pScalingThreshold );
    void SetDefaultThreshold        ( double pDefaultThreshold );
protected:
    //! Constructor.
    KFbxKFCurveFilterConstantKeyReducer(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterConstantKeyReducer *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);

#endif
};




/** Matrix conversion filter.
  * \nosubgrouping
  * \remarks The current implementation of this filter expects to process 9 curves.
  */
class KFBX_DLL KFbxKFCurveFilterMatrixConverter : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterMatrixConverter,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** This filter expects to works with interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
    * \param pAnimStack     Animation stack. 
    * \return               \c false 
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return false; }

    /** Check if the KFbxAnimCurveNodes need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode* pCurveNode[3]);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurves need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** This filter expects to works with interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
      * \param pAnimStack     Animation stack
      * \return               \c false.
      */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return false; }

    /** Apply filter on all the curves of the KFbxAnimCurveNodes.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode* pCurveNode[3]);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode* ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** \enum EMatrixID Matrix ID
      * - \e ePreGlobal
      * - \e ePreTranslate
      * - \e ePostTranslate
      * - \e ePreRotate
      * - \e ePreScale
      * - \e ePostGlobal
      * - \e eScaleOffset
      * - \e eInactivePre
      * - \e eInactivePost
      * - \e eRotationPivot
      * - \e eScalingPivot
      * - \e eMatrixCount
      */
    enum EMatrixID
    {
        ePreGlobal,
        ePreTranslate,
        ePostTranslate,
        ePreRotate,
        ePostRotate,
        ePreScale,
        ePostScale,
        ePostGlobal,
        eScaleOffset,
        eInactivePre,
        eInactivePost,
        eRotationPivot,
        eScalingPivot,
        eMatrixCount
    };

    /** Get the Translation Rotation Scaling source matrix
      * \param pIndex      The matrix ID.
      * \param pMatrix     The matrix used to receive the source matrix.
      */
    void GetSourceMatrix(EMatrixID pIndex, KFbxXMatrix& pMatrix) const;

    /** Set the Translation Rotation Scaling source matrix.
      * \param pIndex      The matrix ID.
      * \param pMatrix     The matrix used to set the source matrix.
      */
    void SetSourceMatrix(EMatrixID pIndex, KFbxXMatrix& pMatrix);

    /** Get the Translation Rotation Scaling destination matrix.
      * \param pIndex      The matrix ID.
      * \param pMatrix     The matrix used to receive the destination matrix.
      */
    void GetDestMatrix(EMatrixID pIndex, KFbxXMatrix& pMatrix) const;

    /** Set the Translation Rotation Scaling destination matrix.
      * \param pIndex      The matrix ID.
      * \param pMatrix     The matrix used to set the destination matrix.
      */
    void SetDestMatrix(EMatrixID pIndex, KFbxXMatrix& pMatrix);

    /** Get the Resampling Period.
      * \return     the Resampling Period.
      */
    KTime GetResamplingPeriod () const;

    /** Set the Resampling period.
      * \param pResamplingPeriod     The Resampling Period to be set.
      */
    void SetResamplingPeriod (KTime& pResamplingPeriod);

    /** Check if the last key is exactly at the end time.
      * \return     \c true if last key is set exactly at end time.
      */
    bool GetGenerateLastKeyExactlyAtEndTime() const;

    /** Set the last key to be is exactly at end time or not
      * \param pFlag     value to set if last key is set exactly at end time.
      */
    void SetGenerateLastKeyExactlyAtEndTime(bool pFlag);

    /** Check if resampling is on frame rate multiple
      * \return     \c true if resampling is on a frame rate multiple.
      */
    bool GetResamplingOnFrameRateMultiple() const;

    /** Set the resample on a frame rate multiple.
      * \param pFlag     The value to be set
      * \remarks         It might be necessary that the starting time of the converted
      *                  animation starts at an multiple of frame period starting from time 0.
      *                  Most softwares play their animation at a definite frame rate, starting
      *                  from time 0.  As resampling occurs when we can't guarantee interpolation,
      *                  keys must match with the moment when the curve is evaluated.
      */
    void SetResamplingOnFrameRateMultiple(bool pFlag);

    /** Get if Apply Unroll is used
      * \return     \c true if unroll is applied.
      */
    bool GetApplyUnroll() const;

    /** Set if Apply Unroll is used
      * \param pFlag     Value to set
      */
    void SetApplyUnroll(bool pFlag);

    /** Get if constant key reducer is used
      * \return     \c true if constant key reducer is applied.
      */
    bool GetApplyConstantKeyReducer() const;

    /** Set if constant key reducer is used
      * \param pFlag     value to set
      */
    void SetApplyConstantKeyReducer(bool pFlag);

    /** Get if the Resample Translation is used
      * \return      \c true if translation data is resampled upon conversion.
      * \remarks     If this flag isn't set, translation data must be calculated
      *              after the conversion process, overriding the resampling process.
      */
    bool GetResampleTranslation() const;

    /** Set the resample translation data.
      * \param pFlag     Value to be set.
      * \remarks         If this flag isn't set, translation data must be calculated
      *                  after the conversion process, overriding the resampling process.
      */
    void SetResampleTranslation(bool pFlag);

    /** Set the Rotation Order of the Source
      * \param pOrder     the order to be set
      */
    void SetSrcRotateOrder(int pOrder);

    /** Set the Rotation Order of the Destination
      * \param pOrder     the order to be set
      */
    void SetDestRotateOrder(int pOrder);

    /** Set to force apply even if source and destination matrices are equivalent
      * \param pVal     If the forces apply is to be used
      */
    void SetForceApply(bool pVal);

    /** Get if the force apply is used
      * \return     \c true if the force apply is used
      */
    bool GetForceApply() const;
///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterMatrixConverter(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterMatrixConverter *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);
#endif
};




/** Resampling filter.
* \nosubgrouping
*/
class KFBX_DLL KFbxKFCurveFilterResample : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterResample,KFbxKFCurveFilter);

public:
    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** Set if the keys are on frame
      * \param pKeysOnFrame     value if keys are set on frame multiples.
      */
    void SetKeysOnFrame(bool pKeysOnFrame);

    /** Get if the keys are on frame
      * \return     Value if keys are on frame multiples.
      */
    bool GetKeysOnFrame() const;

    /** Get the Resampling period
      * \return     The Resampling period
      */
    KTime GetPeriodTime() const;

    /** Set the Resampling Period
      * \param pPeriod     The Resampling Period to be set
      */
    void SetPeriodTime(KTime &pPeriod);


    /** Get the Intelligent Mode
      * \return     the Intelligent Mode
      */
    bool  GetIntelligentMode() const;

    /** Set the Intelligent Mode
      * \param pIntelligent     the Intelligent Mode to be set
      */
    void  SetIntelligentMode( bool pIntelligent );

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterResample(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterResample *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);
#endif

};

/**Unroll filter
  *\nosubgrouping
  * \remarks The current implementation of this filter expects to process 3 curves.
  */
class KFBX_DLL KFbxKFCurveFilterUnroll : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterUnroll,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** This filter expects to works with 3 interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
      * \param pAnimStack     Animation stack
      * \return               \c false.
      */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return false; };

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** This filter expects to works with 3 interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
      * \param pAnimStack     Animation stack
      * \return               \c false.
      */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return false; };

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** Get quality tolerance.
    * \return     The Quality Tolerance
    */
    double GetQualityTolerance() const;

    /** Set quality tolerance.
      * \param pQualityTolerance     Value to be set.
      */
    void SetQualityTolerance(double pQualityTolerance);

    /** Get if the test path is enabled
      * \return     \c true if test for path is enabled.
      */
    bool GetTestForPath() const;

    /** Set if the test path is enabled
      * \param pTestForPath     Value to set if test for path is to be enabled.
      */
    void SetTestForPath(bool pTestForPath);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
    void SetRotationOrder(int pOrder);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterUnroll(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterUnroll *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);
#endif
};


/**GimbleKiller filter
  *\nosubgrouping
  */
class KFBX_DLL KFbxKFCurveFilterGimbleKiller : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterGimbleKiller,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** This filter expects to works with 3 interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
      * \param pAnimStack     Animation stack
      * \return               \c false.
      */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return false; }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

     /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** This filter expects to works with 3 interdependent curves. Passing the animation stack makes no sense
      * since this object would not know which curves to handle.
      * \param pAnimStack     Animation stack
      * \return               \c false.
      */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return false; }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** This filter expects to works with interdependent curves. Receiving one single curve is useless.
      * \return               \c false
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

	//! Return \c true if key sync filter is enabled.
	bool GetApplyKeySyncFilter() const;

	/** Set to \c true to enable key sync filter.
	  * \param pFlag Key sync filter flag.
	  */
	void SetApplyKeySyncFilter(bool pFlag);

 ///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterGimbleKiller(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterGimbleKiller *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);
#endif
};


/**Time shift and scale filter
  *\nosubgrouping
  */
class KFBX_DLL KFbxKFCurveFilterTSS : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterTSS,KFbxKFCurveFilter);

public:

    /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** Get time shift value.
    * \return     The time value used for the shift.
    */
	KTime& GetShift() const;

    /** Set shift.
      * \param pShift     The time value used for the shift.
      */
	void SetShift(KTime& pShift);

    /** Get scale.
    * \return     The Scale Value.
    */
	double GetScale() const;

    /** Set scale.
      * \param pScale     Value to be set.
      */
	void SetScale(double pScale);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterTSS(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterTimeShiftAndScale *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);
#endif
};

/**	\brief Key sync filter.
  * \nosubgrouping
  * Filter to synchronize the keys of a set of function curves.
*/
class KFBX_DLL KFbxKFCurveFilterKeySync : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterKeySync,KFbxKFCurveFilter);

public:
   /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      * \remarks              The current implementation of this filter limits the number of curves on
      *                       the CurveNode to 20.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      * \remarks              The current implementation of this filter limits the number of curves on
      *                       the CurveNode to 20.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterKeySync(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterKeySync *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);

#endif
};

/**	\brief Key scale filter.
  * \nosubgrouping
  * Filter to scale the keys of a set of function curves.
*/
class KFBX_DLL KFbxKFCurveFilterScale : public KFbxKFCurveFilter
{
    KFBXOBJECT_DECLARE(KFbxKFCurveFilterScale,KFbxKFCurveFilter);

public:
   /** Get the Name of the Filter.
      * \return     Pointer to name.
      */
    virtual const char* GetName() const;

    /** Get the Start Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStartTime();
    /** Set the Start Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStartTime(KTime& pTime);
    /** Get the Stop Time.
      * \return     The time expressed as KTime.
      */
    virtual KTime& GetStopTime();

    /** Set the Stopping Time.
      * \param pTime     The time to be set.
      */
    virtual void SetStopTime(KTime& pTime);

    /** Get the Start Key
      * \param pCurve     Curve on which we want to retrieve the start key.
      * \return           The position of the start key.
      */
    virtual int GetStartKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStartKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStartKey(KFCurve& pCurve) const;

    /** Get the Stop Key
      * \param pCurve     Curve on which we want to retrieve the stop key
      * \return           The position of the stop key
      */
    virtual int GetStopKey(KFbxAnimCurve& pCurve) const;
    /** This method is deprecated and should be replaced with a call to GetStopKey(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual int GetStopKey(KFCurve& pCurve) const;

    /** Check if any curves on the animation stack need an application of the filter.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if one or more animated properti(es) need an application of the filter.
    */
    virtual bool NeedApply(KFbxAnimStack* pAnimStack) { return ParentClass::NeedApply(pAnimStack); }

    /** Check if the KFbxAnimCurveNode need an application of the filter.
      * \param pCurveNode     Curves to test if they needs application of filter
      * \return               \c true if the KFbxAnimCurveNode need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool NeedApply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Check if the given KFbxAnimCurve need an application of the filter.
      * \param pCurve         Array of Curves to test if they need the and application of the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if one or more KFbxAnimCurve in an array need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve** pCurve, int pCount);

    /** Check if a KFbxAnimCurve need an application of the filter.
      * \param pCurve         Curve to test if it needs application of filter.
      * \return               \c true if the KFbxAnimCurve need an application of the filter.
      */
    virtual bool NeedApply(KFbxAnimCurve& pCurve);
    /** This method is deprecated and should be replaced with a call to NeedApply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool NeedApply(KFCurve& pCurve);

    /** Retrieve error object.
      * \return     Error object.
      */
    virtual KError* GetError();
    /** Get last error ID.
      * \return     Last error ID.
      */
    virtual int GetLastErrorID() const;
    /** Get last error name.
      * \return     Last error name.
      */
    virtual const char* GetLastErrorString() const;

    /** Apply filter to all the curves stored in the AnimStack.
    * \param pAnimStack     Animation stack where to retrieve the AnimCurves
    * \return               \c true if successful, \c false otherwise.
    */
    virtual bool Apply(KFbxAnimStack* pAnimStack) { return ParentClass::Apply(pAnimStack); }

    /** Apply filter on all the curves of a KFbxAnimCurveNode.
      * \param pCurveNode     Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurveNode& pCurveNode);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurveNode& ...)
    * \param pCurveNode
    * \param pRecursive
    */
    K_DEPRECATED virtual bool Apply(KFCurveNode& pCurveNode, bool pRecursive = true);

    /** Apply filter on the given KFbxAnimCurve.
      * \param pCurve         Array of Curve to apply the filter.
      * \param pCount         Number of Curves in array.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve** pCurve, int pCount);
    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve** ...)
    * \param pCurve
    * \param pCount
    */
    K_DEPRECATED virtual bool Apply(KFCurve** pCurve, int pCount);

    /** Apply filter on a KFbxAnimCurve.
      * \param pCurve         Curve to apply the filter.
      * \return               \c true if successful, \c false otherwise.
      */
    virtual bool Apply(KFbxAnimCurve& pCurve);

    /** This method is deprecated and should be replaced with a call to Apply(KFbxAnimCurve& ...)
    * \param pCurve
    */
    K_DEPRECATED virtual bool Apply(KFCurve& pCurve);

    /** Reset default parameters.
      */
    virtual void Reset();

    /** GetScale.
	  *	\return the current scale factor.
	  */
	float GetScale() const;

	/** SetScale.
      * \param pScale The new scale factor.
	  *	\return
	  */
	void SetScale(float pScale);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//  Anything beyond these lines may not be documented accurately and is
//  subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    //! Constructor.
    KFbxKFCurveFilterScale(KFbxSdkManager& pManager, char const* pName);
    KFCurveFilterScale *mDataCurveFilter;
    virtual void Destruct(bool pRecursive, bool pDependents);

#endif
};

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif // FBXFILESDK_KFBXPLUGINS_KFBXKFCURVEFILTERS_H



