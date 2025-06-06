/* Generated by Together */

#ifndef CPLANEPREFERENCES_H
#define CPLANEPREFERENCES_H

/**
 * 1) � �������� ���� ������ ��������, ������� �� ����� ��������� (� ������).
 * ��� ������ ������� CManuverBuilder ������� � ���� ������ � �������� ������ ������.
 * 2) � �������� ���� ��������� ��� ����������� ����, ��� �������� �����...����������, ���.
 * 3) �������� � ���� �������� ������ ��������.
 */
class CPlanePreferences 
{

	float fMaxSpeed;
	float fStallSpeed;
public:

	void Init( const float _fMaxSpeed )
	{
		fMaxSpeed = _fMaxSpeed;
		fStallSpeed = _fMaxSpeed / 5.0f;
	}
	
	// maneur radius for current speed
	float GetR( const float fSpeed ) const { return 300.0f; }
	float GetStallSpeed() const { return fStallSpeed; }
	float GetMaxSpeed() const { return fMaxSpeed; }
};
#endif //CPLANEPREFERENCES_H