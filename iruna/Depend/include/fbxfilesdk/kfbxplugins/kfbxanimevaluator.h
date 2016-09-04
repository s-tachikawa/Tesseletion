/*!  \file kfbxanimevaluator.h
 */

#ifndef FBXFILESDK_KFBXPLUGINS_KFBXANIMEVALUATOR_H
#define FBXFILESDK_KFBXPLUGINS_KFBXANIMEVALUATOR_H

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
#include <fbxfilesdk/kfbxplugins/kfbxobject.h>
#include <fbxfilesdk/kfbxplugins/kfbxanimevalstate.h>
#include <fbxfilesdk/kfbxplugins/kfbxanimstack.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

struct KFbxAnimEvaluator_prv;

/** This class is an abstract representation of an evaluator object to evaluate animated scenes.
  * \nosubgrouping
  */
class KFBX_DLL KFbxAnimEvaluator : public KFbxObject
{
    KFBXOBJECT_DECLARE_ABSTRACT(KFbxAnimEvaluator, KFbxObject);

public:
    /** Set the evaluator context (animation stack to evaluate).
      * \param pAnimStack Animation Stack to use with this evaluator.
      */
    void SetContext(KFbxAnimStack* pAnimStack);

    /** Get the evaluator context (animation stack to evaluate).     
      * \remarks If no context is set, the first one found in the scene is used if available.
      */
	KFbxAnimStack* GetContext();

    /** Get a node's global transform matrix at the specified time.
      * \param pNode The transform node to evaluate.
      * \param pTime The time used for evaluate. If KTIME_INFINITE is used, this returns the default value, without animation curves evaluation.
	  * \param pPivotSet The pivot set to take into account
	  * \param pApplyTarget Applies the necessary transform to align into the target node
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
	  * \return The resulting global transform of the specified node for the specified time.
      */
	KFbxXMatrix& GetNodeGlobalTransform(KFbxNode* pNode, KTime pTime=KTIME_INFINITE, KFbxNode::EPivotSet pPivotSet=KFbxNode::eSOURCE_SET, bool pApplyTarget=false, bool pForceEval=false);

    /** Get a node's local transform matrix at the specified time.
      * \param pNode The transform node to evaluate.
      * \param pTime The time used for evaluate. If KTIME_INFINITE is used, this returns the default value, without animation curves evaluation.
	  * \param pPivotSet The pivot set to take into account
	  * \param pApplyTarget Applies the necessary transform to align into the target node
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
	  * \return The resulting local transform of the specified node for the specified time.
      */
    KFbxXMatrix& GetNodeLocalTransform(KFbxNode* pNode, KTime pTime=KTIME_INFINITE, KFbxNode::EPivotSet pPivotSet=KFbxNode::eSOURCE_SET, bool pApplyTarget=false, bool pForceEval=false);

    /** Get a property's value at the specified time.
      * \param pProperty The property to evaluate.
      * \param pTime The time used for evaluate.
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
      * \return The property value at the specified time stored in a curve node structure for easier access of complex types.
      */
    KFbxAnimCurveNode& GetPropertyValue(KFbxProperty& pProperty, KTime pTime, bool pForceEval=false);

    /** Validate if the given time value is within animation stack time span range.
      * \param pTime The time value to validate.
      * \return The new validated time, limited by the animation stack time span range.
	  * \remarks If no animation stack are found, time zero is returned.
      */
    KTime ValidateTime(KTime pTime);

    /** Get a node's global transform matrix at the specified time.
      * \param pNode The transform node to evaluate.
      * \param pDirectIndex The index used to retrieve the information in the evaluation state. The first time you evaluate a specific node,
	  *                     it must be set to -1. Then the returned index can be used for a quicker access to the evaluation state array.
      * \param pTime The time used for evaluate. If KTIME_INFINITE is used, this returns the default value, without animation curves evaluation.
	  * \param pPivotSet The pivot set to take into account
	  * \param pApplyTarget Applies the necessary transform to align into the target node
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
	  * \return The resulting global transform of the specified node for the specified time.
      * \remarks If the scene change in the application, all direct indexes must be updated, and the evaluation state cache must be invalidated.
      */
	KFbxXMatrix& GetNodeGlobalTransformFast(KFbxNode* pNode, int& pDirectIndex, KTime pTime=KTIME_INFINITE, KFbxNode::EPivotSet pPivotSet=KFbxNode::eSOURCE_SET, bool pApplyTarget=false, bool pForceEval=false);

    /** Get a node's local transform matrix at the specified time.
      * \param pNode The transform node to evaluate.
      * \param pDirectIndex The index used to retrieve the information in the evaluation state. The first time you evaluate a specific node,
	  *                     it must be set to -1. Then the returned index can be used for a quicker access to the evaluation state array (no find).
      * \param pTime The time used for evaluate. If KTIME_INFINITE is used, this returns the default value, without animation curves evaluation.
	  * \param pPivotSet The pivot set to take into account
	  * \param pApplyTarget Applies the necessary transform to align into the target node
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
	  * \return The resulting local transform of the specified node for the specified time.
      * \remarks If the scene change in the application, all direct indexes must be updated, and the evaluation state cache must be invalidated.
      */
	KFbxXMatrix& GetNodeLocalTransformFast(KFbxNode* pNode, int& pDirectIndex, KTime pTime=KTIME_INFINITE, KFbxNode::EPivotSet pPivotSet=KFbxNode::eSOURCE_SET, bool pApplyTarget=false, bool pForceEval=false);

    /** Get a property's value at the specified time.
      * \param pProperty The property to evaluate.
      * \param pTime The time used for evaluate.
      * \param pDirectIndex The index used to retrieve the information in the evaluation state. The first time you evaluate a specific property,
	  *                     it must be set to -1. Then the returned index can be used for a quicker access to the evaluation state array.
	  * \param pForceEval Force the evaluator to refresh the evaluation state cache even if its already up-to-date.
      * \return The property value at the specified time stored in a curve node structure for easier access of complex types.
      * \remarks If the scene change in the application, all direct indexes must be updated, and the evaluation state cache must be invalidated.
      */
    KFbxAnimCurveNode& GetPropertyValueFast(KFbxProperty& pProperty, int& pDirectIndex, KTime pTime=KTIME_INFINITE, bool pForceEval=false);

    /** Invalidate a node evaluation state cache.
      * \param pNode The node that needs to be re-evaluated in next evaluation.
      */
	void InvalidateNode(KFbxNode* pNode);

    /** Invalidate a property evaluation state cache.
      * \param pProperty The property that needs to be re-evaluated in next evaluation.
      */
	void InvalidateProperty(KFbxProperty& pProperty);

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//    Anything beyond these lines may not be documented accurately and is 
//     subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:
    virtual void EvaluateNodeTransform(KFbxNodeEvalState* pResult, KFbxNode* pNode, KTime pTime, KFbxAnimStack* pStack, KFbxNode::EPivotSet pPivotSet, bool pApplyTarget) = 0;
    virtual void EvaluatePropertyValue(KFbxAnimCurveNode* pResult, KFbxProperty& pProperty, KTime pTime, KFbxAnimStack* pStack) = 0;

    KFbxAnimEvaluator(KFbxSdkManager& pManager, char const* pName);
    virtual void Destruct(bool pRecursive, bool pDependents);

    virtual KFbxObject* Clone(KFbxObject* pContainer, KFbxObject::ECloneType pCloneType) const;
	KFbxAnimEvalState*	GetEvalState(KTime pTime);
	KFbxNodeEvalState*	GetNodeEvalState(KFbxNode* pNode, int& pDirectIndex, KTime pTime, KFbxNode::EPivotSet pPivotSet, bool pApplyTarget, bool pForceEval);

private:
    KFbxAnimEvaluator_prv* mData;

#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS 
};

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif /* FBXFILESDK_KFBXPLUGINS_KFBXANIMEVALUATOR_H */
