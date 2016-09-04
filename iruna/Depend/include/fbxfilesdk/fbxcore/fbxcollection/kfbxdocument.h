/*!  \file kfbxdocument.h
 */

#ifndef FBXFILESDK_FBXCORE_FBXCOLLECTION_KFBXDOCUMENT_H
#define FBXFILESDK_FBXCORE_FBXCOLLECTION_KFBXDOCUMENT_H

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

#include <fbxfilesdk/fbxcore/fbxcollection/kfbxcollection.h>

#include <fbxfilesdk/fbxfilesdk_nsbegin.h>

    // Forward declaration
    class KFbxTakeInfo;
    class KFbxPeripheral;
    class KFbxDocumentInfo;

    /** This class contains objects
      * \nosubgrouping
      * \par
      * This class also provides access to take information.
      *
      */
    class KFBX_DLL KFbxDocument : public KFbxCollection
    {
        KFBXOBJECT_DECLARE(KFbxDocument,KFbxCollection);

	public:
        /**
          * \name Properties
          */
        //@{
            KFbxTypedProperty<fbxReference*>                    Roots;
        //@}

        /**
        * \name Document Member Manager
        */
        //@{
            //! Delete the scene information.
            virtual void    Clear();
            /** Add a member.
			  * \param pMember The member to be added.
			  */
            inline  void    AddRootMember   (KFbxObject *pMember)   { AddMember(pMember); Roots.ConnectSrcObject(pMember); }
            /** Remove a member.
			  * \param pMember The member to be removed.
			  */
            inline  void    RootRootRemoveMember(KFbxObject *pMember)   { RemoveMember(pMember); Roots.DisconnectSrcObject(pMember); }
            /** Find a member.
			  * \param pfbxType Type information.
			  * \param pName Member name.  
			  */
            template <class T> inline T *       FindRootMember(T const *pfbxType, char *pName) { return Roots.FindSrcObject(pfbxType, pName); }

            //! Return the number of objects in the collection.
            inline int                          GetRootMemberCount () const { return Roots.GetSrcObjectCount(); }
            /** Return the number of objects of class T in the collection.
              * \param pFBX_TYPE Type information.
			  * \return The number of objects of class T in the collection.
			  */
            template < class T > inline int     GetRootMemberCount (T const *pFBX_TYPE) const { return Roots.GetSrcObjectCount(T::ClassId); }
			/** Return the number of objects satisfying given criteria in the collection.
			  * \param pCriteria The given criteria.
			  * \return The number of objects satisfying given criteria
			  */
            int                                 GetRootMemberCount( KFbxCriteria pCriteria ) const;

            /** Return the index'th member of the collection.
			  * \param pIndex The member index.
			  */
            inline KFbxObject*                  GetRootMember (int pIndex=0) const                  { return Roots.GetSrcObject(pIndex); }
            /** Return the index'th member of class T of the collection.
			  * \param pFBX_TYPE Type information.
			  * \param pIndex The member index.
			  */
            template < class T > inline T*      GetRootMember (T const *pFBX_TYPE, int pIndex=0) const  { return (T *)Roots.GetSrcObject(T::ClassId,pIndex); }
			/** Return the index'th member of the collection which satisfies given criteria.
              * \param pCriteria The given criteria.
			  * \param pIndex The member index.
			  */
            KFbxObject*                         GetRootMember (KFbxCriteria pCriteria, int pIndex=0) const;
 
			/** Is an object part of the collection.
			  * \param pMember 
			  * \return \c True if pMember is an object part of the collection, \c false otherwise.
			  */
            virtual bool    IsRootMember(KFbxObject *pMember) const;
        //@}


        /**
          * \name Scene information
          */
        //@{
            /** Get the scene information.
              * \return Pointer to the scene information object.
              */
            KFbxDocumentInfo* GetDocumentInfo() const;

            /** Set the scene information.
              * \param pSceneInfo Pointer to the scene information object.
              */
            void SetDocumentInfo(KFbxDocumentInfo* pSceneInfo);
        //@}

        /**
          * \name Offloading management
          *
          * NOTE: The document does not own the peripheral therefore
          * it will not attempt to delete it at destruction time. Also, cloning
          * the document will share the pointer to the peripheral across
          * the cloned objects. And so will do the assignment operator.
          */
        //@{
        public:
            /** Set the current peripheral.
			  * \param pPeripheral The peripheral to be set.
              */
            void SetPeripheral(KFbxPeripheral* pPeripheral);

            /** Retrieve the peripheral of that object.
            * \return Return the current peripheral for that object
            * \remarks A peripheral manipulates the content of an object for instance, a peripheral can load the connections of an object on demand.
            */
            virtual KFbxPeripheral* GetPeripheral();

            /** Offload all the unloadable objects contained in the document using the
              * currently set offload peripheral.
              * \return The number of objects that the document have been able to unload.
              * \remarks Errors that occurred during the operation can be inspected using the
              * GetError() method.
              */
            int UnloadContent();

            /** Load all the objects contained in the document with the data from the
              * currently set offload peripheral.
              * \return The number of objects reloaded.
              * \remarks Errors that occurred during the operation can be inspected using the
              * GetError() method.
              */
            int LoadContent();

        //@}

        /**
          * \name Referencing management
          */
        //@{

            /**
              * Fills an array of pointers to documents that reference objects in this document.
              *
              * \param pReferencingDocuments array of pointers to documents
              * \returns number of documents that reference objects in this document.
              */
            int GetReferencingDocuments(KArrayTemplate<KFbxDocument*> & pReferencingDocuments) const;

            /**
              * Fills an array of pointers to objects in a given document (pFromDoc)
              * that reference objects in this document.
              *
              * \param pFromDoc pointer to the document containing referencing objects.
              * \param pReferencingObjects array of pointers to referencing objects.
              * \returns number of objects that reference objects in this document.
              */
            int GetReferencingObjects(KFbxDocument const * pFromDoc, KArrayTemplate<KFbxObject*> & pReferencingObjects) const;

            /**
              * Fills an array of pointers to documents that are referenced by objects in this document.
              *
              * \param pReferencedDocuments array of pointers to documents
              * \returns number of documents that are referenced by objects in this document.
              */
            int GetReferencedDocuments(KArrayTemplate<KFbxDocument*> & pReferencedDocuments) const;

            /**
              * Fills an array of pointers to objects in a given document (pToDoc)
              * that are referenced by objects in this document.
              *
              * \param pToDoc pointer to the document containing referenced objects.
              * \param pReferencedObjects array of pointers to referenced objects.
              * \returns number of objects that are referenced by objects in this document.
              */
            int GetReferencedObjects(KFbxDocument const * pToDoc, KArrayTemplate<KFbxObject*> & pReferencedObjects) const;

            /**
              * Gets the path string to the root document, if it exists.
              */
            KString GetPathToRootDocument(void) const;
            /**
              * Gets the document path to the root document, if it exists.
			  * \param pDocumentPath array of KFbxDocument to store the document path.
			  * \param pFirstCall
              */
            void GetDocumentPathToRootDocument(KArrayTemplate<KFbxDocument*> & pDocumentPath, bool pFirstCall = true) const;

            /**
              * Tells if this document is a root document.
              */
            bool IsARootDocument(void) { return (NULL == GetDocument()); }
        //@}

        /**
          * \name Animation Stack Management
          */
        //@{
            /** Holds the name of the KFbxAnimStack that the application has decided to use for the animation.
              */
            KFbxTypedProperty<fbxString>    ActiveAnimStackName;

            /** Adds a new AnimStack object to this document.
              * \param pName Created AnimStack name.
              * \return \c true if a new KFbxAnimStack has been successfully created
              * \return \c false if an error occurred or the specified name defines
              * an existing KFbxAnimStack.
              * \return In case of an error, KFbxDocument::GetLastErrorID() will return
              * \c eTAKE_ERROR.
              */
            bool CreateAnimStack(const char* pName);

            /** Create a take.
              * This method is deprecated an should be replaced with calls to CreateAnimStack().
              * \param pName Name of the animation take.
              */
            K_DEPRECATED bool CreateTake(const char* pName);

            /** Destroy the AnimStack object identified by pName from this document.
              * \param pName Name of the AnimStack object to be deleted.
              * \return \c true if the KFbxAnimStack has been destroyed and \c false otherwise.
              */
            bool RemoveAnimStack(const char* pName);

            /** Remove a take.
              * This method is deprecated and should be replaced with calls to RemoveAnimStack().
              * \param pName Name of the animation take.
              */
            K_DEPRECATED bool RemoveTake(const char* pName);

            /** Set the current take.
              * \param pName Name of the take to set.
              * \return \c true if pName identify an existing animation stack and \c false otherwise.
              * This method only stores the received name for Animation Stack selection
              * There is no more the concept of "Current" in the SDK therefore the method has been
              * marked as deprecated and its usage should be avoided. The property \c ActiveAnimStackName
              * can be used to store/retrieve the name of the AnimStack that the application consider as "current".
              * This property may be used when calling the FindMember() to get a pointer to the animation stack.
              */
            K_DEPRECATED bool SetCurrentTake(const char* pName);

            /** Get current take name.
              * This method returns the stored name whether it refers to an existing animation stack or not.
              * There is no more the concept of "Current" in the SDK therefore the method has been marked as
              * deprecated because from now on, the desired animation stack should be passed to the functions
              * that require it.
              * The property \c ActiveAnimStackName replaces this method.
              */
            K_DEPRECATED char* GetCurrentTakeName();

            /** Fill a string array with all existing take names.
              * This method is deprecated and should be replaced with calls to FillAnimStackNameArray().
              * \param pNameArray An array of string objects.
              * \remarks The array of string is cleared before it's used
              */
            K_DEPRECATED void FillTakeNameArray(KArrayTemplate<KString*>& pNameArray);

            /** Fill a string array with all existing animation stack names.
              * \param pNameArray An array of string objects.
              * \remarks The array of string is cleared before it's used
              */
            void FillAnimStackNameArray(KArrayTemplate<KString*>& pNameArray);

        //@}

        /**
          * \name Take Information Management
          */
        //@{

            /** Set take information about an available take.
              * \param pTakeInfo Take information, field KFbxTakeInfo::mName specifies
              * the targeted take.
              * \return \c true if take is found and take information set.
              */
            bool SetTakeInfo(const KFbxTakeInfo& pTakeInfo);

            /** Get take information about an available take.
              * \param pTakeName Take name.
              * \return Pointer to take information or \c NULL if take isn't found or
              *   has no information set.
              */
            KFbxTakeInfo* GetTakeInfo(const KString& pTakeName) const;

        //@}

        /**
          * \name Error Management
          * The same error object is shared among instances of this class.
          */
        //@{

            /** Retrieve error object.
              * \return Reference to error object.
              */
            KError& GetError();

            /** Error identifiers.
              * Most of these are only used internally.
              */
            typedef enum
            {
                eTAKE_ERROR,
                eKFBX_OBJECT_IS_NULL,
                eKFBX_OBJECT_ALREADY_OWNED,
                eKFBX_OBJECT_UNKNOWN,
                eKFBX_MISSING_PERIPHERAL,
                eKFBX_OBJECT_PERIPHERAL_FAILURE,
                eERROR_COUNT
            } EError;

            /** Get last error code.
              * \return Last error code.
              */
            EError GetLastErrorID() const;

            /** Get last error string.
              * \return Textual description of the last error.
              */
            const char* GetLastErrorString() const;

        //@}

        ///////////////////////////////////////////////////////////////////////////////
        //  WARNING!
        //  Anything beyond these lines may not be Documented accurately and is
        //  subject to change without notice.
        ///////////////////////////////////////////////////////////////////////////////
        #ifndef DOXYGEN_SHOULD_SKIP_THIS

				virtual KFbxObject& Copy(const KFbxObject& pObject);
                virtual KFbxObject* Clone(KFbxObject* pContainer, KFbxObject::ECloneType pCloneType) const;

            // Constructor / Destructor
            protected:

                KFbxDocument(KFbxSdkManager& pManager, char const* pName);
                virtual void Construct  (const KFbxDocument* pFrom);
                virtual void Destruct   (bool pRecursive, bool pDependents);
                bool    ConstructProperties(bool pForceSet);

            // Notification and connection management
            protected:
                virtual bool    ConnecNotify (KFbxConnectEvent const &pEvent);
                virtual void    SetDocument(KFbxDocument* pDocument);

            // Helper functions
            public:
                void ConnectVideos();

            // Take management
            protected:
                bool FindTakeName(const KString& pTakeName);

            // this section will exist while the deprecated GetCurrentTakeName() exists
            private:    
                KString mDeprecatedCurrentTakeName;
                
            //
            protected:
                KFbxSdkManager*                     mSdkManager;
                KFbxPeripheral*                     mPeripheral;
                KArrayTemplate<KFbxTakeInfo *>      mTakeInfoArray;
                KError                              mError;
                KFbxDocumentInfo*                   mDocumentInfo;



            friend class KFbxLayerContainer;
            friend class KFbxNodeFinderDuplicateName;
        #endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS
    };

#include <fbxfilesdk/fbxfilesdk_nsend.h>

#endif // FBXFILESDK_FBXCORE_FBXCOLLECTION_KFBXDOCUMENT_H

