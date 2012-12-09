//
// Wolfenstein VR
//
// ComPtr.h created by Geoff Cagle.
// This is a smart ptr class that wraps around COM objects
//
#pragma once
#include <d3d11.h>
#include <cstring> // for NULL

template< typename T >
class ComPtr
{
public:

	// ctors and dtor ///////////////////////////////////////////////////////////

	ComPtr( ) 
		: ptr( NULL )
	{
	}

	ComPtr( T* ptr, bool addRef )
		: ptr( NULL )
	{
		Reset( ptr, addRef );
	}

	template< typename S >
	ComPtr( const ComPtr<S>& comPtr )
		: ptr( NULL )
	{
		Reset( comPtr );
	}

	~ComPtr( )
	{
		Clear( );
	}

	// Get, Reset, InitAsParam, and Clear ////////////////////////////////////////

	T* Get( ) const
	{
		return ptr;
	}

	T** GetAsParam( )
	{
		return &ptr;
	}

	void Reset( T* newPtr, bool addRef )
	{
		if( newPtr && addRef )
			newPtr->AddRef;

		if( ptr )
			ptr->Release( );

		ptr = newPtr;
	}

	T** InitAsParam( )
	{
		Clear( );
		return &ptr;
	}

	void Clear( )
	{
		if( ptr )
		{
			ptr->Release( );
			ptr = NULL;
		}
	}

	template< typename S >
	void Reset( const ComPtr<S>& comPtr )
	{
		Reset( static_cast<T*>( comPtr.ptr ), true );
	}
	
	// Casting and assignment ////////////////////////////////////////////////////

	operator T*( ) const
	{
		return Get( );
	}

	operator bool( ) const
	{
		return ptr != NULL;
	}

	T* operator->( ) const
	{
		return ptr;
	}

	T& operator*( ) const
	{
		return *ptr;
	}

	template< typename S >
	ComPtr<T>& operator=( const ComPtr<S>& comPtr )
	{
		Reset( comPtr );
		return *this;
	}

	// Helper Methods ///////////////////////////////////////////////////////////

	template< typename S >
	HRESULT QueryInterface( ComPtr<S>& comPtr )
	{
		comPtr.Clear( );

		if( ptr )
		{
			HRESULT hr = ptr->QueryInterface( __uuidof(S), reinterpret_cast<void**>(comPtr.InitAsParam()) );

			if( comPtr )
				comPtr->AddRef( );

			return hr;
		}

		return S_FALSE;
	}

private:

	T* ptr;
};