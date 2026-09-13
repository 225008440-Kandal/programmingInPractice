#include <stdio.h>

int main()
{
    double basic = 0, housingAllow = 0, transportAllow = 0, taxAmount = 0;
    double gross = 0, net = 0, totalAllowances = 0;

    printf("=== EMPLOYEE SALARY CALCULATOR ===\n\n");

    printf("Basic salary      : ");
    scanf("%lf", &basic);

    printf("Housing allowance : ");
    scanf("%lf", &housingAllow);

    printf("Transport allowance: ");
    scanf("%lf", &transportAllow);

    printf("Tax deducted      : ");
    scanf("%lf", &taxAmount);

    totalAllowances = housingAllow + transportAllow;
    gross = basic + totalAllowances;
    net = gross - taxAmount;

    printf("\n==================================\n");
    printf("Basic salary      : %10.2f\n", basic);
    printf("Total allowances  : %10.2f\n", totalAllowances);
    printf("----------------------------------\n");
    printf("Gross Salary      : %10.2f\n", gross);
    printf("Tax               : %10.2f\n", taxAmount);
    printf("----------------------------------\n");
    printf("Net Salary        : %10.2f\n", net);

    return 0;
}